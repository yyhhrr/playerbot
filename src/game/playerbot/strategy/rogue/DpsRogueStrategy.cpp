#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueMultipliers.h"
#include "DpsRogueStrategy.h"

using namespace ai;


NextAction** DpsRogueStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void DpsRogueStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("melee", 10.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"high energy available",
		NextAction::array(0, new NextAction("mutilate", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "combo points available",
        NextAction::array(0, new NextAction("kidney shot", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium threat",
		NextAction::array(0, new NextAction("vanish", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"low health",
		NextAction::array(0, new NextAction("evasion", 50.0f), new NextAction("feint", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"kick",
		NextAction::array(0, new NextAction("kick", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("backstab", 21.0f), NULL)));
}

void DpsRogueStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* DpsRogueStrategy::createAction(const char* name)
{
    if (!strcmp("mutilate", name))
    {
        return new ActionNode ("mutilate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sinister strike"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("sinister strike", name))
    {
        return new ActionNode ("sinister strike",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("kidney shot", name))
	{
		return new ActionNode ("kidney shot",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("rupture"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("rupture", name))
	{
		return new ActionNode ("rupture",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("slice and dice"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("slice and dice", name))
	{
		return new ActionNode ("slice and dice",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("eviscerate"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("eviscerate", name))
	{
		return new ActionNode ("eviscerate",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("vanish", name))
	{
		return new ActionNode ("vanish",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("evasion", name))
	{
		return new ActionNode ("evasion",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("kick", name))
	{
		return new ActionNode ("kick",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("feint", name))
	{
		return new ActionNode ("feint",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (!strcmp("backstab", name))
    {
        return new ActionNode ("backstab",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mutilate"), NULL),
            /*C*/ NULL);
    }
	else return CombatStrategy::createAction(name);
}
