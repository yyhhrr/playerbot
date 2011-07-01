#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DestroyItemAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;

bool DestroyItemAction::Execute(Event event)
{
    string text = event.getParam();
    ItemIds ids = chat->parseItems(text);

    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
        DestroyItem(&FindItemByIdVisitor(*i));

    return true;
}

void DestroyItemAction::DestroyItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item *item = visitor->GetResult();
    if (item) {
        bot->DestroyItem(item->GetBagSlot(),item->GetSlot(), true);
        ostringstream out; out << chat->formatItem(item->GetProto()) << " destroyed";
        ai->TellMaster(out);
    }
}
