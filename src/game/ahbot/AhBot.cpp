#include "Category.h"
#include "ItemBag.h"
#include "AhBot.h"
#include "../World.h"
#include "Policies/SingletonImp.h"
#include "Config/Config.h"
#include "../Chat.h"

using namespace ahbot;

bool ChatHandler::HandleAhBotCommand(char* args)
{
    auctionbot.HandleCommand(args);
    return true;
}

INSTANTIATE_SINGLETON_1( ahbot::AhBot );

uint32 AhBot::auctionIds[MAX_AUCTIONS] = {2, 6, 7};
extern Category* Categories[MAX_AHBOT_CATEGORIES];

void AhBot::Init()
{
    uint32 account = sConfig.GetIntDefault("AhBot.Account", 0);
    uint32 guid = sConfig.GetIntDefault("AhBot.GUID", 0);
    if (!account || !guid)
        return;

    session = new WorldSession(account, NULL, SEC_PLAYER, true, 0, LOCALE_enUS);
    player = new Player(session);
    player->MinimalLoadFromDB(NULL, guid);

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
    return ObjectGuid((uint64)sConfig.GetIntDefault("AhBot.GUID", 0));
}

void AhBot::Update()
{
    if (!player)
        return;

    time_t now = time(0);

    if (now < nextAICheckTime)
        return;

    nextAICheckTime = time(0) + sConfig.GetIntDefault("AhBot.UpdateIntervalInSeconds", 60);

    ForceUpdate();
}

void AhBot::ForceUpdate()
{
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

    for (int i = 0; i < sizeof(Categories) / sizeof(Category*); i++)
        Update(auction, Categories[i], inAuctionItems);

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
    AuctionHouseObject::AuctionEntryMap* auctionEntryMap = auctionHouse->GetAuctions();

    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap->begin(); itr != auctionEntryMap->end(); ++itr)
    {
        AuctionEntry *entry = itr->second;
        if (entry->owner == player->GetGUIDLow() || entry->bidder == player->GetGUIDLow())
            continue;

        Item *item = sAuctionMgr.GetAItem(entry->itemGuidLow);
        if (!item)
            continue;

        uint32 price = category->GetPrice(item->GetProto(), auctionIds[auction]);
        if (!price || !item->GetCount())
            continue;
        uint32 bidPrice = item->GetCount() * price;
        uint32 buyoutPrice = item->GetCount() * urand(price, price * 2);
        
        uint32 curPrice = entry->bid;
        if (!curPrice) curPrice = entry->startbid;
        if (!curPrice) curPrice = entry->buyout;

        if (curPrice > buyoutPrice)
            continue;

        if (entry->bidder && entry->bidder != player->GetGUIDLow())
            player->GetSession()->SendAuctionOutbiddedMail(entry);
        
        entry->bidder = player->GetGUIDLow();
        entry->bid = urand(curPrice + 1, buyoutPrice);

        if (100 * (buyoutPrice - entry->bid) / price > 25)
        {
            CharacterDatabase.PExecute("UPDATE auction SET buyguid = '%u',lastbid = '%u' WHERE id = '%u'", 
                entry->bidder, entry->bid, entry->Id);

            sLog.outDetail("AhBot placed bid %d for %s in auction %d", entry->bid, item->GetProto()->Name1, auction);
        }
        else
        {
            entry->bid = entry->buyout;
            entry->AuctionBidWinning(player);

            sLog.outDetail("AhBot won %s in auction %d for %d", item->GetProto()->Name1, auction, entry->buyout);
        }
   }
}

void AhBot::AddAuctions(int auction, Category* category, ItemBag* inAuctionItems)
{
    vector<uint32>& inAuction = inAuctionItems->Get(category);

    int32 maxAllowedAuctionCount = category->GetMaxAllowedAuctionCount();
    if (inAuctionItems->GetCount(category) >= maxAllowedAuctionCount)
        return;

    maxAllowedAuctionCount = urand(maxAllowedAuctionCount, maxAllowedAuctionCount * 2);

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

    uint32 price = category->GetPrice(proto, auctionIds[auction]);
    uint32 stackCount = category->GetStackCount(proto);
    if (!price || !stackCount)
        return;

    uint32 bidPrice = stackCount * price;
    uint32 buyoutPrice = stackCount * urand(price, price * 2);
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

    for (int i=0; i<MAX_AHBOT_CATEGORIES; i++)
    {
        Category* category = Categories[i];
        if (category->Contains(proto))
        {
            for (int auction = 0; auction < MAX_AUCTIONS; auction++)
            {
                ostringstream out; 
                out << proto->Name1 << " (" << category->GetName() << ") - auction house " << auctionIds[auction] << " - sell: " 
                    << category->GetPrice(proto, auctionIds[auction]) << ", buy: " << category->GetBuyPrice(proto, auctionIds[auction]);
                sLog.outString(out.str().c_str());
            }
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

    AuctionHouseObject::AuctionEntryMap* auctions = auctionHouse->GetAuctions();
    AuctionHouseObject::AuctionEntryMap::iterator itr;
    itr = auctions->begin();

    uint32 guid = sConfig.GetIntDefault("AhBot.GUID", 0);

    while (itr != auctions->end())
    {
        if (itr->second->owner == guid)
            itr->second->expireTime = sWorld.GetGameTime();

        ++itr;
    }

    sLog.outDetail("AhBot's auctions marked as expired in auction %d", auctionIds[auction]);
}

void AhBot::AddToHistory(AuctionEntry* entry, uint32 won)
{
    if (entry->bidder == player->GetGUIDLow())
        return;

    ItemPrototype const* proto = sObjectMgr.GetItemPrototype(entry->itemTemplate);
    if (!proto)
        return;

    string category = "";
    for (int i = 0; i < MAX_AHBOT_CATEGORIES; i++)
    {
        if (Categories[i]->Contains(proto))
        {
            category = Categories[i]->GetName();
            break;
        }
    }

    uint32 now = time(0);
    CharacterDatabase.PExecute("INSERT INTO ahbot_history (buytime, item, bid, buyout, category, won, auction_house) "
        "VALUES ('%u', '%u', '%u', '%u', '%s', '%u', '%u')", 
        now, entry->itemTemplate, entry->bid ? entry->bid : entry->startbid, entry->buyout, 
        category.c_str(), won, entry->auctionHouseEntry->houseId);
}


void AhBot::CleanupHistory()
{
    uint32 when = time(0) - 3600 * 24 * sConfig.GetIntDefault("AhBot.History.Days", 30);
    CharacterDatabase.PExecute("DELETE FROM ahbot_history WHERE buytime < '%u'", when);
}