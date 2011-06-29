#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericPaladinStrategy.h"

using namespace ai;

void GenericPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice snare",
        NextAction::array(0, new NextAction("hammer of justice", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("divine shield", 50.0f), new NextAction("holy light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("divine protection on party", 40.0f), new NextAction("holy light on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"hammer of justice interrupt",
		NextAction::array(0, new NextAction("hammer of justice", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("lay on hands", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member critical health",
		NextAction::array(0, new NextAction("lay on hands on party", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"target critical health",
		NextAction::array(0, new NextAction("hammer of wrath", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse cure magic",
		NextAction::array(0, new NextAction("cleanse", 41.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse party member cure magic",
		NextAction::array(0, new NextAction("cleanse magic on party", 40.0f), NULL)));
}


ActionNode* GenericPaladinStrategy::GetAction(string name)
{
    if (name == "seal of light")
    {
        return new ActionNode ("seal of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL),
            /*C*/ NULL);
    }
	else if (name == "cleanse")
    {
        return new ActionNode ("cleanse",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify"), NULL),
            /*C*/ NULL);
    }
    else if (name == "cleanse poison on party")
    {
        return new ActionNode ("cleanse poison on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify poison on party"), NULL),
            /*C*/ NULL);
    }
	else if (name == "cleanse disease on party")
	{
		return new ActionNode ("cleanse disease on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("purify disease on party"), NULL),
			/*C*/ NULL);
	}
    else if (name == "seal of wisdom")
    {
        return new ActionNode ("seal of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL),
            /*C*/ NULL);
    }
    else if (name == "seal of justice")
    {
        return new ActionNode ("seal of justice",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of righteousness"), NULL),
            /*C*/ NULL);
    }
    else if (name == "hand of reckoning")
    {
        return new ActionNode ("hand of reckoning",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of justice"), NULL),
            /*C*/ NULL);
    }
    else if (name == "judgement of wisdom")
    {
        return new ActionNode ("judgement of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of light"), NULL),
            /*C*/ NULL);
    }
    else if (name == "divine shield")
    {
        return new ActionNode ("divine shield",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("divine protection"), NULL),
            /*C*/ NULL);
    }
    else if (name == "flash of light")
    {
        return new ActionNode ("flash of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light"), NULL),
            /*C*/ NULL);
    }
    else if (name == "flash of light on party")
    {
        return new ActionNode ("flash of light on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light on party"), NULL),
            /*C*/ NULL);
    }
    else if (name == "holy wrath")
    {
        return new ActionNode ("holy wrath",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("consecration"), NULL),
            /*C*/ NULL);
    }
	else return CombatStrategy::GetAction(name);
}
