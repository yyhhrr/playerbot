#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MeleeCombatStrategy.h"

using namespace ai;


void MeleeCombatStrategy::InitTriggers(list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_NORMAL + 9), NULL)));
}
