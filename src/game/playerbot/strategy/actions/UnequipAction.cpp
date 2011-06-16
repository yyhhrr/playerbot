#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "UnequipAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;
void extractItemIds(const string& text, list<uint32>& itemIds);

bool UnequipAction::Execute(Event event)
{
    string text = event.getParam();

    list<uint32> ids; /* = */ extractItemIds(text, ids);

    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        UnequipItem(&FindItemByIdVisitor(*i));

    return true;
}


void UnequipAction::UnequipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item *item = visitor->GetResult();
    if (item) UnequipItem(*item);
}

void UnequipAction::UnequipItem(Item& item)
{
    uint8 bagIndex = item.GetBagSlot();
    uint8 slot = item.GetSlot();
    uint8 dstBag = NULL_BAG; 
    

    WorldPacket* const packet = new WorldPacket(CMSG_AUTOSTORE_BAG_ITEM, 3);
    *packet << bagIndex << slot << dstBag;
    bot->GetSession()->QueuePacket(packet);
}

