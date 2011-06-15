#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ItemCountValue.h"

using namespace ai;

void extractItemIds(const string& text, list<uint32>& itemIds);

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

    const char* name = qualifier.c_str();
    list<uint32> ids; /* = */ extractItemIds(name, ids);
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
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

    list<uint32> ids; /* = */ extractItemIds(qualifier.c_str(), ids);
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        return Find(FindItemByIdVisitor(*i));

    return NULL;
}

uint32 InventoryItemValue::TextToItemQuality( const char* text ) 
{
    uint32 quality = MAX_ITEM_QUALITY;

    if (strstr(text, "poor") || strstr(text, "gray"))
        quality = ITEM_QUALITY_POOR;
    else if (strstr(text, "normal") || strstr(text, "white"))
        quality = ITEM_QUALITY_NORMAL;
    else if (strstr(text, "uncommon") || strstr(text, "green"))
        quality = ITEM_QUALITY_UNCOMMON;
    else if (strstr(text, "rare") || strstr(text, "blue"))
        quality = ITEM_QUALITY_RARE;
    else if (strstr(text, "epic") || strstr(text, "violet"))
        quality = ITEM_QUALITY_EPIC;

    return quality;
}
