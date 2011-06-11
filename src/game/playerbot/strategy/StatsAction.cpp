#include "../../pchdef.h"
#include "../playerbot.h"
#include "StatsAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool StatsAction::ExecuteResult()
{
    ostringstream out;

    ListGold(out);
    out << ", ";
    ListBagSlots(out);
    out << ", ";
    ListXP(out);
    out << ", ";
    ListRepairCost(out);

    TellMaster(out);
    return true;
}

void StatsAction::ListGold(ostringstream &out)
{
    uint32 copper = GetBot()->GetMoney();
    uint32 gold = uint32(copper / 10000);
    copper -= (gold * 10000);
    uint32 silver = uint32(copper / 100);
    copper -= (silver * 100);

    out << "|r|cff00ff00" << gold << "|r|cfffffc00g|r|cff00ff00" << silver << "|r|cffcdcdcds|r|cff00ff00" << copper << "|r|cffffd333c";
}

void StatsAction::ListBagSlots(ostringstream &out)
{
    uint32 totalused = 0;
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        const Item* const pItem = GetBot()->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
            totalused++;
    }
    uint32 totalfree = 16 - totalused;
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) GetBot()->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            ItemPrototype const* pBagProto = pBag->GetProto();
            if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
                totalfree =  totalfree + pBag->GetFreeSlots();
        }

    }

    out << "|h|cff00ff00" << totalfree << "|h|cffffffff bag slots";
}

void StatsAction::ListXP( ostringstream &out )
{
    uint32 curXP = GetBot()->GetUInt32Value(PLAYER_XP);
    uint32 nextLevelXP = GetBot()->GetUInt32Value(PLAYER_NEXT_LEVEL_XP);
    uint32 xpPercent = 0;
    if (nextLevelXP)
        xpPercent = 100 * curXP / nextLevelXP;

    out << "|r|cff00ff00" << xpPercent << "|r|cffffd333%" << "|h|cffffffff XP";
}

void StatsAction::ListRepairCost(ostringstream &out)
{
    uint32 copper = EstRepairAll();
    uint32 gold = uint32(copper / 10000);
    copper -= (gold * 10000);
    uint32 silver = uint32(copper / 100);
    copper -= (silver * 100);

    out << "|r|cff00ff00" << gold << "|r|cfffffc00g|r|cff00ff00" << silver << "|r|cffcdcdcds|r|cff00ff00" << copper << "|r|cffffd333c"
        << "|h|cffffffff repair";
}

uint32 StatsAction::EstRepairAll()
{
    uint32 TotalCost = 0;
    // equipped, backpack, bags itself
    for(int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        TotalCost += EstRepair(( (INVENTORY_SLOT_BAG_0 << 8) | i ));

    // bank, buyback and keys not repaired

    // items in inventory bags
    for(int j = INVENTORY_SLOT_BAG_START; j < INVENTORY_SLOT_BAG_END; ++j)
        for(int i = 0; i < MAX_BAG_SIZE; ++i)
            TotalCost += EstRepair(( (j << 8) | i ));
    return TotalCost;
}

uint32 StatsAction::EstRepair(uint16 pos)
{
    Item* item = GetBot()->GetItemByPos(pos);

    uint32 TotalCost = 0;
    if(!item)
        return TotalCost;

    uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
    if(!maxDurability)
        return TotalCost;

    uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

    uint32 LostDurability = maxDurability - curDurability;
    if(LostDurability>0)
    {
        ItemPrototype const *ditemProto = item->GetProto();

        DurabilityCostsEntry const *dcost = sDurabilityCostsStore.LookupEntry(ditemProto->ItemLevel);
        if(!dcost)
        {
            sLog.outError("RepairDurability: Wrong item lvl %u", ditemProto->ItemLevel);
            return TotalCost;
        }

        uint32 dQualitymodEntryId = (ditemProto->Quality+1)*2;
        DurabilityQualityEntry const *dQualitymodEntry = sDurabilityQualityStore.LookupEntry(dQualitymodEntryId);
        if(!dQualitymodEntry)
        {
            sLog.outError("RepairDurability: Wrong dQualityModEntry %u", dQualitymodEntryId);
            return TotalCost;
        }

        uint32 dmultiplier = dcost->multiplier[ItemSubClassToDurabilityMultiplierId(ditemProto->Class,ditemProto->SubClass)];
        uint32 costs = uint32(LostDurability*dmultiplier*double(dQualitymodEntry->quality_mod));

        if (costs==0)                                   //fix for ITEM_QUALITY_ARTIFACT
            costs = 1;

        TotalCost = costs;
    }
    return TotalCost;
}