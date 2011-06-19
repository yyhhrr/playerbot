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
    if (name == "defensive stance") 
    {
        return new ActionNode ("defensive stance",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return GenericNonCombatStrategy::GetAction(name);
}
