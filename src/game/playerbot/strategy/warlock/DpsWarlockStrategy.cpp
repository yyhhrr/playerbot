#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "DpsWarlockStrategy.h"
#include "WarlockActions.h"

using namespace ai;

NextAction** DpsWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void DpsWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"shadow trance",
		NextAction::array(0, new NextAction("shadow bolt", 20.0f), NULL)));
}


ActionNode* DpsWarlockStrategy::createAction(const char* name)
{
    if (!strcmp("summon imp", name)) 
    {
        return new ActionNode ("summon imp",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else 
        return GenericWarlockStrategy::createAction(name);
}


