#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "GenericMageStrategy.h"

using namespace ai;

void GenericMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close",
        NextAction::array(0, new NextAction("frost nova", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("counterspell", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("ice block", 80.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "polymorph",
        NextAction::array(0, new NextAction("polymorph", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"spellsteal",
		NextAction::array(0, new NextAction("spellsteal", 40.0f), NULL)));
}


ActionNode* GenericMageStrategy::createAction(const char* name)
{
    if (!strcmp("frostbolt", name))
    {
        return new ActionNode ("frostbolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("fireball", name))
    {
        return new ActionNode ("fireball",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("pyroblast", name))
    {
        return new ActionNode ("pyroblast",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("flamestrike", name))
    {
        return new ActionNode ("flamestrike",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("fire blast", name))
    {
        return new ActionNode ("fire blast",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("scorch"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("scorch", name))
    {
        return new ActionNode ("scorch",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
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
    else if (!strcmp("frost nova", name))
    {
        return new ActionNode ("frost nova",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("flee"), NULL));
    }
    else if (!strcmp("counterspell", name))
    {
        return new ActionNode ("counterspell",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("remove curse", name))
    {
        return new ActionNode ("remove curse",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("remove curse on party", name))
    {
        return new ActionNode ("remove curse on party",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("icy veins", name) || !strcmp("boost", name))
    {
        return new ActionNode ("icy veins",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("combustion", name) || !strcmp("boost", name))
    {
        return new ActionNode ("combustion",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("ice block", name))
	{
		return new ActionNode ("ice block",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (!strcmp("polymorph", name))
    {
        return new ActionNode ("polymorph",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("spellsteal", name))
	{
		return new ActionNode ("spellsteal",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else return CombatStrategy::createAction(name);
}
