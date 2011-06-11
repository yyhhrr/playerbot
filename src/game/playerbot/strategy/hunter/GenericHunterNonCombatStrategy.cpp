#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterMultipliers.h"
#include "GenericHunterNonCombatStrategy.h"

using namespace ai;

void HunterBuffSpeedNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "aspect of the pack", 
        NextAction::array(0, new NextAction("aspect of the pack", 1.0f), NULL)));
}

void GenericHunterNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "has attackers", 
        NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet", 
        NextAction::array(0, new NextAction("call pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet dead", 
        NextAction::array(0, new NextAction("revive pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet low health", 
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));
}


ActionNode* GenericHunterNonCombatStrategy::GetAction(const char* name)
{
    if (!strcmp("call pet", name)) 
    {
        return new ActionNode ("call pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("reach spell", name)) 
    {
        return new ActionNode ("reach spell",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flee", name)) 
    {
        return new ActionNode ("flee",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mend pet", name)) 
    {
        return new ActionNode ("mend pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("revive pet", name)) 
    {
        return new ActionNode ("revive pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("rapid fire", name) || !strcmp("boost", name)) 
    {
        return new ActionNode ("rapid fire",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("readyness"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("readyness", name)) 
    {
        return new ActionNode ("readyness",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the hawk", name)) 
    {
        return new ActionNode ("aspect of the hawk",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the wild", name)) 
    {
        return new ActionNode ("aspect of the wild",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the viper", name)) 
    {
        return new ActionNode ("aspect of the viper",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the pack", name)) 
    {
        return new ActionNode ("aspect of the pack",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the cheetah", name)) 
    {
        return new ActionNode ("aspect of the cheetah",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }

    return GenericNonCombatStrategy::GetAction(name);
}