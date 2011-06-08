#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "../GenericTriggers.h"
#include "../GenericActions.h"
#include "GenericHunterStrategy.h"
#include "HunterActionFactory.h"

using namespace ai;

ActionFactory* GenericHunterStrategy::createActionFactory() 
{
    return new HunterActionFactory(ai); 
}

void GenericHunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close", 
        NextAction::array(0, new NextAction("flee", 50.0f), new NextAction("concussive shot", 40.0f), NULL)));    
    
    triggers.push_back(new TriggerNode(
        "hunters pet dead", 
        NextAction::array(0, new NextAction("revive pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet low health", 
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "rapid fire",
        NextAction::array(0, new NextAction("rapid fire", 55.0f), NULL)));
}

ActionNode* GenericHunterStrategy::createAction(const char* name)
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
    else return CombatStrategy::createAction(name);
}
