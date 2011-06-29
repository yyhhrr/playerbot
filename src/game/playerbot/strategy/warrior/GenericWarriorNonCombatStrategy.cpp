#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "GenericWarriorNonCombatStrategy.h"

using namespace ai;

void GenericWarriorNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
}

ActionNode* GenericWarriorNonCombatStrategy::GetAction(string name)
{
    return GenericNonCombatStrategy::GetAction(name);
}
