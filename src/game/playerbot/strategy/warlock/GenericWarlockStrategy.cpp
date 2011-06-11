#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockStrategy.h"

using namespace ai;

NextAction** GenericWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void GenericWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "curse of agony",
        NextAction::array(0, new NextAction("curse of agony", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("drain life", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"target critical health",
		NextAction::array(0, new NextAction("drain soul", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "banish",
        NextAction::array(0, new NextAction("banish", 21.0f), NULL)));
}


ActionNode* GenericWarlockStrategy::GetAction(const char* name)
{
    if (!strcmp("immolate", name)) 
    {
        return new ActionNode ("immolate",  
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
    else if (!strcmp("corruption", name)) 
    {
        return new ActionNode ("corruption",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("summon voidwalker", name)) 
    {
        return new ActionNode ("summon voidwalker",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("curse of agony", name)) 
    {
        return new ActionNode ("curse of agony",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shadow bolt", name)) 
    {
        return new ActionNode ("shadow bolt",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain soul", name)) 
    {
        return new ActionNode ("drain soul",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain mana", name)) 
    {
        return new ActionNode ("drain mana",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain life", name)) 
    {
        return new ActionNode ("drain life",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("banish", name)) 
    {
        return new ActionNode ("banish",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return CombatStrategy::GetAction(name);
}


