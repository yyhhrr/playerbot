#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TellItemCountAction.h"
#include "../values/ItemCountValue.h"

using namespace ai;

bool TellItemCountAction::Execute(Event event)
{
    
    string text = event.getParam();

    uint32 quality = InventoryItemValue::TextToItemQuality(text);
    if (quality == MAX_ITEM_QUALITY)
    {
        uint8 count = AI_VALUE2(uint8, "item count", text);

        if (!count)
            return false;

        ostringstream out;
        out << text << "x" << (int)count;
        ai->TellMaster(out.str());

        return true;
    }

    FindItemsToTradeByQualityVisitor visitor(quality, 100);
    IterateItems(&visitor);
    list<Item*> found = visitor.GetResult();
    for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
        TellItem((*i)->GetProto(), (*i)->GetCount());

    return true;
}
