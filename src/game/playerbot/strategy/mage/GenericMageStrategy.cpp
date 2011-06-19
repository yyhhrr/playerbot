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


ActionNode* GenericMageStrategy::GetAction(string name)
{
    if (name == "frostbolt")
    {
        return new ActionNode ("frostbolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NULL);
    }
    else if (name == "fireball")
    {
        return new ActionNode ("fireball",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "pyroblast")
    {
        return new ActionNode ("pyroblast",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "flamestrike")
    {
        return new ActionNode ("flamestrike",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "fire blast")
    {
        return new ActionNode ("fire blast",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("scorch"), NULL),
            /*C*/ NULL);
    }
    else if (name == "scorch")
    {
        return new ActionNode ("scorch",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
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
    else if (name == "frost nova")
    {
        return new ActionNode ("frost nova",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("flee"), NULL));
    }
    else if (name == "counterspell")
    {
        return new ActionNode ("counterspell",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "remove curse")
    {
        return new ActionNode ("remove curse",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "remove curse on party")
    {
        return new ActionNode ("remove curse on party",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "icy veins" || name == "boost")
    {
        return new ActionNode ("icy veins",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "combustion" || name == "boost")
    {
        return new ActionNode ("combustion",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (name == "ice block")
	{
		return new ActionNode ("ice block",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (name == "polymorph")
    {
        return new ActionNode ("polymorph",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (name == "spellsteal")
	{
		return new ActionNode ("spellsteal",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else return CombatStrategy::GetAction(name);
}
