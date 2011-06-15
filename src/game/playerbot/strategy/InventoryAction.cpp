#include "../../pchdef.h"
#include "../playerbot.h"
#include "InventoryAction.h"
#include "../PlayerbotAI.h"
#include "ItemCountValue.h"

using namespace ai;

void InventoryAction::IterateItems(IterateItemsVisitor* visitor, IterateItemsMask mask)
{
    if (mask & ITERATE_ITEMS_IN_BAGS)
        IterateItemsInBags(visitor);

    if (mask & ITERATE_ITEMS_IN_EQUIP)
        IterateItemsInEquip(visitor);
}

void InventoryAction::IterateItemsInBags(IterateItemsVisitor* visitor)
{
    Player* bot = ai->GetBot();

    for(int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            if (!visitor->Visit(pItem))
                return;

    for(int i = KEYRING_SLOT_START; i < CURRENCYTOKEN_SLOT_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            if (!visitor->Visit(pItem))
                return;

    for(int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        if (Bag *pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            for(uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
                    if (!visitor->Visit(pItem))
                        return;
}

void InventoryAction::IterateItemsInEquip(IterateItemsVisitor* visitor)
{
    Player* bot = ai->GetBot();

    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if(!pItem)
            continue;

        if (!visitor->Visit(pItem))
            return;
    }
}


void InventoryAction::TellItem(ItemPrototype const * proto, int count) 
{
    ostringstream out;

    char color[32];
    sprintf(color, "%x", ItemQualityColors[proto->Quality]);

    out << " |c" << color << "|Hitem:" << proto->ItemId
        << ":0:0:0:0:0:0:0" << "|h[" << proto->Name1
        << "]|h|r";
    if (count > 1)
        out << "x" << count;

    ai->TellMaster(out);
}

