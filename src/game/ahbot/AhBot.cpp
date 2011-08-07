#include "Category.h"
#include "ItemBag.h"
#include "AhBot.h"
#include "../World.h"
#include "Policies/SingletonImp.h"
#include "Config/Config.h"
#include "../Chat.h"
#include "AhBotConfig.h"

using namespace ahbot;

bool Player::MinimalLoadFromDB( QueryResult *result, uint32 guid )
{
    bool delete_result = true;
    if (!result)
    {
        //                                        0     1           2           3           4    5          6          7
        result = CharacterDatabase.PQuery("SELECT name, position_x, position_y, position_z, map, totaltime, leveltime, at_login FROM characters WHERE guid = '%u'",guid);
        if (!result)
            return false;
    }
    else
        delete_result = false;

    Field *fields = result->Fetch();

    // overwrite possible wrong/corrupted guid
    Object::_Create( guid, 0, HIGHGUID_PLAYER );

    m_name = fields[0].GetCppString();

    Relocate(fields[1].GetFloat(),fields[2].GetFloat(),fields[3].GetFloat());
    SetLocationMapId(fields[4].GetUInt32());

    m_Played_time[PLAYED_TIME_TOTAL] = fields[5].GetUInt32();
    m_Played_time[PLAYED_TIME_LEVEL] = fields[6].GetUInt32();

    m_atLoginFlags = fields[7].GetUInt32();

    if (delete_result)
        delete result;

    for (int i = 0; i < PLAYER_SLOTS_COUNT; ++i)
        m_items[i] = NULL;

    if (HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
        m_deathState = DEAD;

    return true;
}

bool ChatHandler::HandleAhBotCommand(char* args)
{
    auctionbot.HandleCommand(args);
    return true;
}

INSTANTIATE_SINGLETON_1( ahbot::AhBot );

uint32 AhBot::auctionIds[MAX_AUCTIONS] = {2, 6, 7};

void AhBot::Init()
{
    sAhBotConfig.Initialize();

    if (!sAhBotConfig.enabled)
        return;

    session = new WorldSession(sAhBotConfig.account, NULL, SEC_PLAYER, true, 0, LOCALE_enUS);
    player = new Player(session);
    player->MinimalLoadFromDB(NULL, GetAHBplayerGUID());

    ObjectAccessor::Instance().AddObject(player);

    availableItems.Init();
}

AhBot::~AhBot()
{
    if (player)
    {
        ObjectAccessor::Instance().RemoveObject(player);
        delete player;
        delete session;
    }
}

ObjectGuid AhBot::GetAHBplayerGUID()
{
    return ObjectGuid(sAhBotConfig.guid);
}

void AhBot::Update()
{
    time_t now = time(0);

    if (now < nextAICheckTime)
        return;

    nextAICheckTime = time(0) + sAhBotConfig.updateInterval;

    ForceUpdate();
}

void AhBot::ForceUpdate()
{
    if (!player)
        return;

    sLog.outString("AhBot is now checking auctions");

    for (int i = 0; i < MAX_AUCTIONS; i++)
    {
        InAuctionItemsBag inAuctionItems(auctionIds[i]);
        Update(i, &inAuctionItems);
    }
}

void AhBot::Update(int auction, ItemBag* inAuctionItems)
{
    inAuctionItems->Init(true);

    for (int i = 0; i < CategoryList::instance.size(); i++)
        Update(auction, CategoryList::instance[i], inAuctionItems);

    CleanupHistory();
}

void AhBot::Update(int auction, Category* category, ItemBag* inAuctionItems)
{
    Answer(auction, category, inAuctionItems);
    AddAuctions(auction, category, inAuctionItems);
}

void AhBot::Answer(int auction, Category* category, ItemBag* inAuctionItems)
{
    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if(!ahEntry)
        return;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);
    AuctionHouseObject::AuctionEntryMap const& auctionEntryMap = auctionHouse->GetAuctions();

    int64 availableMoney = GetAvailableMoney(auctionIds[auction]);

    vector<AuctionEntry*> entries;
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap.begin(); itr != auctionEntryMap.end(); ++itr)
        entries.push_back(itr->second);

    Shuffle(entries);

    for (vector<AuctionEntry*>::iterator itr = entries.begin(); itr != entries.end(); ++itr)
    {
        AuctionEntry *entry = *itr;
        if (entry->owner == player->GetGUIDLow() || entry->bidder == player->GetGUIDLow())
            continue;

        Item *item = sAuctionMgr.GetAItem(entry->itemGuidLow);
        if (!item)
            continue;

        uint32 price = category->GetPricingStrategy()->GetBuyPrice(item->GetProto(), auctionIds[auction]);
        if (!price || !item->GetCount())
            continue;
        uint32 bidPrice = item->GetCount() * price;
        uint32 buyoutPrice = item->GetCount() * urand(price, 4 * price / 3);

        uint32 curPrice = entry->bid;
        if (!curPrice) curPrice = entry->startbid;
        if (!curPrice) curPrice = entry->buyout;

        if (curPrice > buyoutPrice)
            continue;

        if (availableMoney < curPrice)
            continue;

        if (entry->bidder && entry->bidder != player->GetGUIDLow())
            player->GetSession()->SendAuctionOutbiddedMail(entry);

        entry->bidder = player->GetGUIDLow();
        entry->bid = curPrice + urand(1, 1 + bidPrice / 10);
        availableMoney -= curPrice;

        if (entry->buyout && (entry->bid >= entry->buyout || 100 * (entry->buyout - entry->bid) / price < 25))
        {
            entry->bid = entry->buyout;
            entry->AuctionBidWinning(NULL);

            sLog.outDetail("AhBot won %s in auction %d for %d", item->GetProto()->Name1, auction, entry->buyout);
        }
        else
        {
            CharacterDatabase.PExecute("UPDATE auction SET buyguid = '%u',lastbid = '%u' WHERE id = '%u'",
                entry->bidder, entry->bid, entry->Id);

            sLog.outDetail("AhBot placed bid %d for %s in auction %d", entry->bid, item->GetProto()->Name1, auction);
        }
   }
}

void AhBot::AddAuctions(int auction, Category* category, ItemBag* inAuctionItems)
{
    vector<uint32>& inAuction = inAuctionItems->Get(category);

    int32 maxAllowedAuctionCount = category->GetMaxAllowedAuctionCount();
    if (inAuctionItems->GetCount(category) >= maxAllowedAuctionCount)
        return;

    maxAllowedAuctionCount = urand(1 + maxAllowedAuctionCount / 2, maxAllowedAuctionCount);

    vector<uint32>& available = availableItems.Get(category);
    for (vector<uint32>::iterator i = available.begin(); i != available.end(); i++)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(*i);
        if (!proto)
            continue;

        if (inAuctionItems->GetCount(category) >= maxAllowedAuctionCount)
            break;

        if (inAuctionItems->GetCount(category, proto->ItemId) >= category->GetMaxAllowedItemAuctionCount(proto))
            continue;

        inAuctionItems->Add(proto);
        AddAuction(auction, category, proto);
    }
}

void AhBot::AddAuction(int auction, Category* category, ItemPrototype const* proto)
{
    Item* item = Item::CreateItem(proto->ItemId, 1, player);
    if (!item)
        return;

    uint32 randomPropertyId = Item::GenerateItemRandomPropertyId(proto->ItemId);
    if (randomPropertyId)
        item->SetItemRandomProperties(randomPropertyId);

    item->AddToUpdateQueueOf(player);

    uint32 price = category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction]);
    uint32 stackCount = category->GetStackCount(proto);
    if (!price || !stackCount)
        return;

    uint32 bidPrice = stackCount * price;
    uint32 buyoutPrice = stackCount * urand(price, 4 * price / 3);
    item->SetCount(stackCount);

    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if(!ahEntry)
        return;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);

    AuctionEntry* auctionEntry = new AuctionEntry;
    auctionEntry->Id = sObjectMgr.GenerateAuctionID();
    auctionEntry->itemGuidLow = item->GetGUIDLow();
    auctionEntry->itemTemplate = item->GetEntry();
    auctionEntry->owner = player->GetGUIDLow();
    auctionEntry->startbid = bidPrice;
    auctionEntry->buyout = buyoutPrice;
    auctionEntry->bidder = 0;
    auctionEntry->bid = 0;
    auctionEntry->deposit = 0;
    auctionEntry->expireTime = (time_t) (urand(8, 24) * 60 * 60 + time(NULL));
    auctionEntry->moneyDeliveryTime = 0;
    auctionEntry->auctionHouseEntry = ahEntry;
    item->SaveToDB();
    item->RemoveFromUpdateQueueOf(player);

    sAuctionMgr.AddAItem(item);

    auctionHouse->AddAuction(auctionEntry);
    auctionEntry->SaveToDB();

    sLog.outDetail("AhBot added %d of %s to auction %d for %d..%d", stackCount, proto->Name1, auction, bidPrice, buyoutPrice);
}

void AhBot::HandleCommand(string command)
{
    if (!player)
        return;

    if (command == "expire")
    {
        for (int i = 0; i < MAX_AUCTIONS; i++)
            Expire(i);

        return;
    }

    if (command == "update")
    {
        ForceUpdate();
        return;
    }

    uint32 itemId = atoi(command.c_str());
    if (!itemId)
    {
        sLog.outString("ahbot expire - expire all auctions");
        sLog.outString("ahbot update - update all auctions");
        sLog.outString("ahbot <itemId> - show item price");
        return;
    }

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
    if (!proto)
        return;

    for (int i=0; i<CategoryList::instance.size(); i++)
    {
        Category* category = CategoryList::instance[i];
        if (category->Contains(proto))
        {
            ostringstream out;
            out << proto->Name1 << " (" << category->GetDisplayName() << ")"
                << "\n";
            for (int auction = 0; auction < MAX_AUCTIONS; auction++)
            {
                out << "--- auction house " << auctionIds[auction] <<  "(money: "
                    << GetAvailableMoney(auctionIds[auction])
                    << ") ---\n";

                out << "sell: " << category->GetPricingStrategy()->GetSellPrice(proto, auctionIds[auction])
                    << " ("  << category->GetPricingStrategy()->ExplainSellPrice(proto, auctionIds[auction]) << ")"
                    << "\n";

                out << "buy: " << category->GetPricingStrategy()->GetBuyPrice(proto, auctionIds[auction])
                    << " ("  << category->GetPricingStrategy()->ExplainBuyPrice(proto, auctionIds[auction]) << ")"
                    << "\n";
            }
            sLog.outString(out.str().c_str());
            break;
        }
    }
}

void AhBot::Expire(int auction)
{
    if (!player)
        return;

    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionIds[auction]);
    if(!ahEntry)
        return;

    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);

    AuctionHouseObject::AuctionEntryMap const& auctions = auctionHouse->GetAuctions();
    AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctions.begin();

    while (itr != auctions.end())
    {
        if (itr->second->owner == sAhBotConfig.guid)
            itr->second->expireTime = sWorld.GetGameTime();

        ++itr;
    }

    sLog.outDetail("AhBot's auctions marked as expired in auction %d", auctionIds[auction]);
}

void AhBot::AddToHistory(AuctionEntry* entry)
{
    if (!player)
        return;

    if (entry->bidder != player->GetGUIDLow() && entry->owner != player->GetGUIDLow())
        return;

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(entry->itemTemplate);
    if (!proto)
        return;

    string category = "";
    for (int i = 0; i < CategoryList::instance.size(); i++)
    {
        if (CategoryList::instance[i]->Contains(proto))
        {
            category = CategoryList::instance[i]->GetName();
            break;
        }
    }

    uint32 won = AHBOT_WON_PLAYER;
    if (entry->bidder == player->GetGUIDLow())
        won = AHBOT_WON_SELF;

    uint32 now = time(0);
    CharacterDatabase.PExecute("INSERT INTO ahbot_history (buytime, item, bid, buyout, category, won, auction_house) "
        "VALUES ('%u', '%u', '%u', '%u', '%s', '%u', '%u')",
        now, entry->itemTemplate, entry->bid ? entry->bid : entry->startbid, entry->buyout,
        category.c_str(), won, entry->auctionHouseEntry->houseId);
}


void AhBot::CleanupHistory()
{
    uint32 when = time(0) - 3600 * 24 * sAhBotConfig.historyDays;
    CharacterDatabase.PExecute("DELETE FROM ahbot_history WHERE buytime < '%u'", when);
}

uint32 AhBot::GetAvailableMoney(uint32 auctionHouse)
{
    int64 result = sAhBotConfig.alwaysAvailableMoney;

    map<uint32, uint32> data;
    data[AHBOT_WON_PLAYER] = 0;
    data[AHBOT_WON_SELF] = 0;

    QueryResult* results = CharacterDatabase.PQuery(
        "SELECT won, SUM(bid) FROM ahbot_history WHERE auction_house = '%u' GROUP BY won HAVING won > 0 ORDER BY won",
        auctionHouse);
    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            data[fields[0].GetUInt32()] = fields[1].GetUInt32();

        } while (results->NextRow());

        delete results;
    }

    results = CharacterDatabase.PQuery(
        "SELECT max(buytime) FROM ahbot_history WHERE auction_house = '%u' AND won = '2'",
        auctionHouse);
    if (results)
    {
        Field* fields = results->Fetch();
        uint32 lastBuyTime = fields[0].GetUInt32();
        uint32 now = time(0);
        if (lastBuyTime && now > lastBuyTime)
        result += (now - lastBuyTime) / 3600 / 24 * sAhBotConfig.alwaysAvailableMoney;

        delete results;
    }

    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionHouse);
    if(!ahEntry)
        return result;

    AuctionHouseObject::AuctionEntryMap const& auctionEntryMap = sAuctionMgr.GetAuctionsMap(ahEntry)->GetAuctions();
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap.begin(); itr != auctionEntryMap.end(); ++itr)
    {
        AuctionEntry *entry = itr->second;
        if (entry->bidder != player->GetGUIDLow())
            continue;

        result -= entry->bid;
    }

    result += (data[AHBOT_WON_PLAYER] - data[AHBOT_WON_SELF]);
    return result < 0 ? 0 : (uint32)result;
}
