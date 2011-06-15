#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "EquipAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;

void extractItemIds(const string& text, list<uint32>& itemIds);

bool EquipAction::Execute(Event event)
{
    string text = event.getParam();

    list<uint32> ids; /* = */ extractItemIds(text, ids);

    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
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
    Player* bot = ai->GetBot();

    WorldPacket* const packet = new WorldPacket(CMSG_AUTOEQUIP_ITEM, 2);
    *packet << bagIndex << slot;
    bot->GetSession()->QueuePacket(packet);
}
