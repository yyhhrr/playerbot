#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "FleeStrategy.h"

using namespace ai;

void FleeStrategy::InitTriggers(list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "panic",
        NextAction::array(0, new NextAction("flee", 100.0f), NULL)));
}
