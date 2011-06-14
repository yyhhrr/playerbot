#include "../../pchdef.h"
#include "../playerbot.h"
#include "TellItemCountAction.h"
#include "../PlayerbotAI.h"
#include "ItemCountValue.h"

using namespace ai;

bool TellItemCountAction::Execute(Event event)
{
    Player* bot = ai->GetAi()->GetBot();
    string text = event.getParam();

    uint32 quality = InventoryItemValue::TextToItemQuality(text.c_str());
    if (quality == MAX_ITEM_QUALITY)
    {
        uint8 count = AI_VALUE2(uint8, "item count", text.c_str());

        if (!count)
            return false;

        ostringstream out;
        out << text << "x" << (int)count;
        ai->GetAi()->TellMaster(out.str().c_str());

        return true;
    }

    FindItemsToTradeByQualityVisitor visitor(quality, 100);
    ai->GetInventoryManager()->IterateItems(&visitor);
    list<Item*> found = visitor.GetResult();
    for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
        ai->GetInventoryManager()->TellItem((*i)->GetProto(), (*i)->GetCount());

    return true;
}
