#include "../../pchdef.h"
#include "../playerbot.h"
#include "QueryItemUsageAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool QueryItemUsageAction::Execute(Event event)
{
    string text = event.getParam();

    list<uint32> items; /* = */ ai->GetInventoryManager()->extractItemIds(text, items);
    QueryItemsUsage(items);   
    return false;
}

void QueryItemUsageAction::QueryItemUsage(ItemPrototype const *item)
{
    Player *bot = ai->GetAi()->GetBot();
    if (bot->CanUseItem(item) != EQUIP_ERR_OK)
        return;

    if (item->InventoryType == INVTYPE_NON_EQUIP)
        return;

    uint16 eDest;
    uint8 msg = bot->CanEquipNewItem(NULL_SLOT, eDest, item->ItemId, true);
    if( msg != EQUIP_ERR_OK )
        return;

    Item* existingItem = bot->GetItemByPos(eDest);
    if (!existingItem)
    {
        ai->GetAi()->TellMaster("Equip");
        return;
    }

    bool equip = false;
    const ItemPrototype* oldItem = existingItem->GetProto();
    if (oldItem->ItemLevel < item->ItemLevel && oldItem->ItemId != item->ItemId)
    {
        switch (item->Class)
        {
        case ITEM_CLASS_ARMOR:
            equip = (oldItem->SubClass <= item->SubClass);
            break;
        default:
            equip = true;
        }
    }

    if (equip)
    {
        ostringstream out;
        out << "Replace +";
        out << (item->ItemLevel - oldItem->ItemLevel);
        out << " lvl";
        ai->GetAi()->TellMaster(out.str().c_str());
    }
}

void QueryItemUsageAction::QueryItemsUsage(list<uint32> items) 
{
    for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *item = sItemStorage.LookupEntry<ItemPrototype>(*i);
        QueryItemUsage(item);
    }
}