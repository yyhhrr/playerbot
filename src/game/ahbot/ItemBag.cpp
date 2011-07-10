#include "Category.h"
#include "ItemBag.h"

using namespace ahbot;

Other Other::instance;
Equip Equip::instance;
Recipe Recipe::instance;
Reagent Reagent::instance;
Enchant Enchant::instance;
Trade Trade::instance;
ahbot::Quest ahbot::Quest::instance;
Consumable Consumable::instance;

Category* Categories[MAX_AHBOT_CATEGORIES] = 
{
    &Other::instance,
    &Equip::instance,
    &Recipe::instance,
    &Reagent::instance,
    &Enchant::instance,
    &Trade::instance,
    &ahbot::Quest::instance,
    &Consumable::instance
};

ItemBag::ItemBag()
{
    for (int i = 0; i < MAX_AHBOT_CATEGORIES; i++)
    {
        content[Categories[i]] = vector<uint32>();
    }
}

void ItemBag::Init(bool silent) 
{
    if (silent)
    {
        Load();
        return;
    }

    sLog.outString("Loading/Scanning %s...", GetName().c_str());

    Load(); 

    for (int i = 0; i < MAX_AHBOT_CATEGORIES; i++)
    {
        Category* category = Categories[i];
        Shuffle(content[category]);
        sLog.outString("loaded %d %s items", content[category].size(), category->GetName().c_str());
    }
}

void ItemBag::Shuffle(vector<uint32>& items) 
{
    uint32 count = items.size();
    for (uint32 i = 0; i < count * 5; i++)
    {
        int i1 = urand(0, count - 1);
        int i2 = urand(0, count - 1);
        
        uint32 item = items[i1];
        items[i1] = items[i2];
        items[i2] = item;
    }
}

int32 ItemBag::GetCount(Category* category, uint32 item)
{
    uint32 count = 0;

    vector<uint32>& items = content[category];
    for (vector<uint32>::iterator i = items.begin(); i != items.end(); ++i)
    {
        if (*i == item)
            count++;
    }

    return count;
}

bool ItemBag::Add(ItemPrototype const* proto)
{
    if (!proto ||
        proto->Bonding == BIND_WHEN_PICKED_UP ||
        proto->Bonding == BIND_QUEST_ITEM)
        return false;

    for (int i = 0; i < MAX_AHBOT_CATEGORIES; i++)
    {
        if (Categories[i]->Contains(proto))
        {
            content[Categories[i]].push_back(proto->ItemId);
            return true;
        }
    }

    return false;
}

void AvailableItemsBag::Load()
{
    for (uint32 itemId = 0; itemId < sItemStorage.MaxEntry; ++itemId)
    {
        Add(sObjectMgr.GetItemPrototype(itemId));
    }

}

void InAuctionItemsBag::Load()
{
    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(auctionId);
    if(!ahEntry)
        return;
    
    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(ahEntry);
    AuctionHouseObject::AuctionEntryMap* auctionEntryMap = auctionHouse->GetAuctions();
    for (AuctionHouseObject::AuctionEntryMap::const_iterator itr = auctionEntryMap->begin(); itr != auctionEntryMap->end(); ++itr)
    {
        AuctionEntry *Aentry = itr->second;
        Item *item = sAuctionMgr.GetAItem(Aentry->itemGuidLow);
        if (!item)
            continue;
        
        Add(item->GetProto());
    }
}

string InAuctionItemsBag::GetName()
{
    ostringstream out; out << "auction house " << auctionId;
    return out.str();
}
