#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ItemCountValue.h"

using namespace ai;

uint8 ItemCountValue::Calculate()
{
    Player* bot = InventoryAction::ai->GetBot();

    if (qualifier == "food")
    {
    	FindFoodVisitor visitor(bot, 11);
        return Find(visitor) ? 1 : 0;
    }

    if (qualifier == "drink")
    {
    	FindFoodVisitor visitor(bot, 59);
        return Find(visitor) ? 1 : 0;
    }

    if (qualifier == "mana potion")
    {
    	FindFoodVisitor visitor(bot, 438);
        return Find(visitor) ? 1 : 0;
    }

    if (qualifier == "healing potion")
    {
    	FindFoodVisitor visitor(bot, 441);
        return Find(visitor) ? 1 : 0;
    }

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

list<Item*> InventoryItemValue::Calculate()
{
    list<Item*> result;

    Player* bot = InventoryAction::ai->GetBot();

    if (qualifier == "food")
    {
    	FindFoodVisitor visitor(bot, 11);
    	Item* item = Find(visitor);
    	if (item)
    	    result.push_back(item);
    }

    if (qualifier == "drink")
    {
    	FindFoodVisitor visitor(bot, 59);
        Item* item = Find(visitor);
        if (item)
            result.push_back(item);
    }

    if (qualifier == "mana potion")
    {
    	FindFoodVisitor visitor(bot, 438);
        Item* item = Find(visitor);
        if (item)
            result.push_back(item);
    }

    if (qualifier == "healing potion")
    {
    	FindFoodVisitor visitor(bot, 441);
        Item* item = Find(visitor);
        if (item)
            result.push_back(item);
    }

    list<Item*> items = InventoryAction::parseItems(qualifier);
    for (list<Item*>::iterator i = items.begin(); i != items.end(); i++)
        result.push_back(*i);

    return result;
}
