#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "GenericMageNonCombatStrategy.h"

using namespace ai;

void GenericMageNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane intellect", 
        NextAction::array(0, new NextAction("arcane intellect", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane intellect on party", 
        NextAction::array(0, new NextAction("arcane intellect on party", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no drink", 
		NextAction::array(0, new NextAction("conjure water", 16.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no food", 
		NextAction::array(0, new NextAction("conjure food", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mage armor", 
        NextAction::array(0, new NextAction("mage armor", 19.0f), NULL)));
}


ActionNode* GenericMageNonCombatStrategy::createAction(const char* name)
{
    ActionNode* node = GenericMageStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("arcane intellect", name)) 
    {
        return new ActionNode ("arcane intellect",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("arcane intellect on party", name)) 
    {
        return new ActionNode ("arcane intellect on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("conjure water", name)) 
	{
		return new ActionNode ("conjure water",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("conjure food", name)) 
	{
		return new ActionNode ("conjure food",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("mage armor", name)) 
    {
        return new ActionNode ("mage armor",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("ice armor"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("ice armor", name)) 
    {
        return new ActionNode ("ice armor",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frost armor"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("frost armor", name)) 
    {
        return new ActionNode ("frost armor",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }

    return GenericMageStrategy::createAction(name);
}