#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "EquipAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;

bool EquipAction::Execute(Event event)
{
    string text = event.getParam();
    ItemIds ids = chat->parseItems(text);

    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
        EquipItem(&FindItemByIdVisitor(*i));

    return true;
}

void EquipAction::EquipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item *item = visitor->GetResult();
    if (item) EquipItem(*item);
}


void EquipAction::EquipItem(Item& item)
{
    uint8 bagIndex = item.GetBagSlot();
    uint8 slot = item.GetSlot();


    WorldPacket* const packet = new WorldPacket(CMSG_AUTOEQUIP_ITEM, 2);
    *packet << bagIndex << slot;
    bot->GetSession()->QueuePacket(packet);

    ostringstream out; out << chat->formatItem(item.GetProto()) << " equipped";
    ai->TellMaster(out);
}
