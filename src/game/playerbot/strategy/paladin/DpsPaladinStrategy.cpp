#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "DpsPaladinStrategy.h"

using namespace ai;

NextAction** DpsPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("crusader strike", 10.0f), NULL);
}

void DpsPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "judgement of wisdom", 
        NextAction::array(0, new NextAction("judgement of wisdom", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing", 
        NextAction::array(0, new NextAction("blessing of might", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe", 
		NextAction::array(0, new NextAction("divine storm", 27.0f), new NextAction("consecration", 27.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"art of war", 
		NextAction::array(0, new NextAction("exorcism", 27.0f), NULL)));
}

void DpsPaladinStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* DpsPaladinStrategy::createAction(const char* name)
{
    if (!strcmp("seal of command", name)) 
    {
        return new ActionNode ("seal of command",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of wisdom"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("blessing of might", name)) 
    {
        return new ActionNode ("blessing of might",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blessing of kings"), NULL), 
            /*C*/ NULL);
    }
	else if (!strcmp("divine storm", name)) 
	{
		return new ActionNode ("divine storm",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("crusader strike", name)) 
	{
		return new ActionNode ("crusader strike",  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("melee"), NULL),
			/*C*/ NULL);
	}
    else return GenericPaladinStrategy::createAction(name);
}