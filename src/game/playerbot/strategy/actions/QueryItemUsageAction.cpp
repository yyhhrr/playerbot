#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "QueryItemUsageAction.h"


using namespace ai;


bool QueryItemUsageAction::Execute(Event event)
{
    string text = event.getParam();

    ItemIds items = chat->parseItems(text);
    QueryItemsUsage(items);   
    return false;
}

void QueryItemUsageAction::QueryItemUsage(ItemPrototype const *item)
{
    Player *bot = ai->GetBot();
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
        ai->TellMaster("Equip");
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
        ai->TellMaster(out.str());
    }
}

void QueryItemUsageAction::QueryItemsUsage(ItemIds items) 
{
    for (ItemIds::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *item = sItemStorage.LookupEntry<ItemPrototype>(*i);
        QueryItemUsage(item);
    }
}