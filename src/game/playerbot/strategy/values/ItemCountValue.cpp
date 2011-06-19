#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ItemCountValue.h"

using namespace ai;

uint8 ItemCountValue::Calculate()
{
    Player* bot = InventoryAction::ai->GetBot();

    if (qualifier == "food")
        return Find(FindFoodVisitor(bot, 11)) ? 1 : 0;

    if (qualifier == "drink")
        return Find(FindFoodVisitor(bot, 59)) ? 1 : 0;

    if (qualifier == "mana potion")
        return Find(FindFoodVisitor(bot, 438)) ? 1 : 0;

    if (qualifier == "healing potion")
        return Find(FindFoodVisitor(bot, 441)) ? 1 : 0;

    string name = qualifier;
    ItemIds ids = InventoryAction::chat->parseItems(qualifier);
    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
    {
        ItemPrototype const *item = sItemStorage.LookupEntry<ItemPrototype>(*i);
        QueryItemCountVisitor visitor(item->ItemId);
        IterateItems(&visitor, ITERATE_ALL_ITEMS);

        int count = visitor.GetCount();
        if (count)
            return count;
    }

    QueryNamedItemCountVisitor visitor(name);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);
    return visitor.GetCount();
}

Item* ItemCountValue::Find(FindItemVisitor &visitor)
{
    IterateItems(&visitor, ITERATE_ALL_ITEMS);
    return visitor.GetResult();
}

Item* InventoryItemValue::Find(FindItemVisitor &visitor)
{
    IterateItems(&visitor, ITERATE_ALL_ITEMS);
    return visitor.GetResult();
}

Item* InventoryItemValue::Calculate()
{
    Player* bot = InventoryAction::ai->GetBot();

    if (qualifier == "food")
        return Find(FindFoodVisitor(bot, 11));

    if (qualifier == "drink")
        return Find(FindFoodVisitor(bot, 59));

    if (qualifier == "mana potion")
        return Find(FindFoodVisitor(bot, 438));

    if (qualifier == "healing potion")
        return Find(FindFoodVisitor(bot, 441));

    ItemIds ids = InventoryAction::chat->parseItems(qualifier);
    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
        return Find(FindItemByIdVisitor(*i));

    return NULL;
}

uint32 InventoryItemValue::TextToItemQuality( string text ) 
{
    uint32 quality = MAX_ITEM_QUALITY;

    if (text == "poor" || text == "gray")
        quality = ITEM_QUALITY_POOR;
    else if (text == "normal" || text == "white")
        quality = ITEM_QUALITY_NORMAL;
    else if (text == "uncommon" || text == "green")
        quality = ITEM_QUALITY_UNCOMMON;
    else if (text == "rare" || text == "blue")
        quality = ITEM_QUALITY_RARE;
    else if (text == "epic" || text == "violet")
        quality = ITEM_QUALITY_EPIC;

    return quality;
}
