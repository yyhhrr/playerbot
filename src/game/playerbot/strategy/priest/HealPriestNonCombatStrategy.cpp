#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestNonCombatStrategy.h"

using namespace ai;

void HealPriestNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "power word: fortitude", 
        NextAction::array(0, new NextAction("power word: fortitude", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party", 
        NextAction::array(0, new NextAction("power word: fortitude on party", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit", 
        NextAction::array(0, new NextAction("divine spirit", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party", 
        NextAction::array(0, new NextAction("divine spirit on party", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "inner fire", 
        NextAction::array(0, new NextAction("inner fire", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("flash heal", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("flash heal on party", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("resurrection", 20.0f), NULL)));
}

void HealPriestNonCombatStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* HealPriestNonCombatStrategy::createAction(const char* name)
{
    ActionNode* node = CombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("inner fire", name)) 
    {
        return new ActionNode ("inner fire",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shadowform", name)) 
    {
        return new ActionNode ("shadowform",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("remove shadowform", name)) 
    {
        return new ActionNode ("remove shadowform",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("holy nova", name)) 
    {
        return new ActionNode ("holy nova",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: fortitude", name)) 
    {
        return new ActionNode ("power word: fortitude",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: fortitude on party", name)) 
    {
        return new ActionNode ("power word: fortitude on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine spirit", name)) 
    {
        return new ActionNode ("divine spirit",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine spirit on party", name)) 
    {
        return new ActionNode ("divine spirit on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    if (!strcmp("power word: shield", name)) 
    {
        return new ActionNode ("power word: shield",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("power word: shield on party", name)) 
    {
        return new ActionNode ("power word: shield on party",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("renew", name)) 
    {
        return new ActionNode ("renew",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("renew on party", name)) 
    {
        return new ActionNode ("renew on party",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("greater heal", name)) 
    {
        return new ActionNode ("greater heal",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("greater heal on party", name)) 
    {
        return new ActionNode ("greater heal on party",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("heal on party"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("heal", name)) 
    {
        return new ActionNode ("heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("heal on party", name)) 
    {
        return new ActionNode ("heal on party",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("lesser heal", name)) 
    {
        return new ActionNode ("lesser heal",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("lesser heal on party", name)) 
    {
        return new ActionNode ("lesser heal on party",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flash heal", name)) 
    {
        return new ActionNode ("flash heal",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("flash heal on party", name)) 
    {
        return new ActionNode ("flash heal on party",  
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dispel magic", name)) 
    {
        return new ActionNode ("dispel magic",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dispel magic on party", name)) 
    {
        return new ActionNode ("dispel magic on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("dispel magic on target", name)) 
    {
        return new ActionNode ("dispel magic on target",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure disease", name)) 
    {
        return new ActionNode ("cure disease",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure disease on party", name)) 
    {
        return new ActionNode ("cure disease on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish disease", name)) 
    {
        return new ActionNode ("abolish disease",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish disease on party", name)) 
    {
        return new ActionNode ("abolish disease on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("fade", name)) 
    {
        return new ActionNode ("fade",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("resurrection", name)) 
	{
		return new ActionNode ("resurrection",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return CombatStrategy::createAction(name);
}



