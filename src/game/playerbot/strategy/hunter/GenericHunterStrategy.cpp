#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericHunterStrategy.h"
#include "HunterAiObjectContext.h"

using namespace ai;

AiObjectContext* GenericHunterStrategy::createAiObjectContext() 
{
    return new HunterAiObjectContext(ai); 
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

ActionNode* GenericHunterStrategy::GetAction(string name)
{
    if (name == "call pet") 
    {
        return new ActionNode ("call pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "reach spell") 
    {
        return new ActionNode ("reach spell",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "flee") 
    {
        return new ActionNode ("flee",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "mend pet") 
    {
        return new ActionNode ("mend pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "revive pet") 
    {
        return new ActionNode ("revive pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "rapid fire" || name == "boost") 
    {
        return new ActionNode ("rapid fire",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("readyness"), NULL), 
            /*C*/ NULL);
    }
    else if (name == "readyness") 
    {
        return new ActionNode ("readyness",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "aspect of the hawk") 
    {
        return new ActionNode ("aspect of the hawk",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "aspect of the wild") 
    {
        return new ActionNode ("aspect of the wild",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "aspect of the viper") 
    {
        return new ActionNode ("aspect of the viper",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "aspect of the pack") 
    {
        return new ActionNode ("aspect of the pack",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), NULL), 
            /*C*/ NULL);
    }
    else if (name == "aspect of the cheetah") 
    {
        return new ActionNode ("aspect of the cheetah",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return CombatStrategy::GetAction(name);
}
