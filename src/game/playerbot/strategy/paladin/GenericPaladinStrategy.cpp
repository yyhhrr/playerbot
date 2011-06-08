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


ActionNode* GenericPaladinStrategy::createAction(const char* name)
{
    if (!strcmp("seal of light", name))
    {
        return new ActionNode ("seal of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("devotion aura", name))
    {
        return new ActionNode ("devotion aura",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("consecration", name))
    {
        return new ActionNode ("consecration",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("cleanse", name))
    {
        return new ActionNode ("cleanse",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("purify", name))
    {
        return new ActionNode ("purify",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("cleanse poison on party", name))
    {
        return new ActionNode ("cleanse poison on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify poison on party"), NULL),
            /*C*/ NULL);
    }
	else if (!strcmp("cleanse disease on party", name))
	{
		return new ActionNode ("cleanse disease on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("purify disease on party"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("cleanse magic on party", name))
	{
		return new ActionNode ("cleanse magic on party",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (!strcmp("purify poison on party", name))
    {
        return new ActionNode ("purify poison on party",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("purify disease on party", name))
	{
		return new ActionNode ("purify disease on party",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (!strcmp("seal of wisdom", name))
    {
        return new ActionNode ("seal of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("seal of justice", name))
    {
        return new ActionNode ("seal of justice",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of righteousness"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("seal of righteousness", name))
    {
        return new ActionNode ("seal of righteousness",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("hand of reckoning", name))
    {
        return new ActionNode ("hand of reckoning",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of justice"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("avenger's shield", name))
    {
        return new ActionNode ("avenger's shield",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("exorcism", name))
    {
        return new ActionNode ("exorcism",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("judgement of light", name))
    {
        return new ActionNode ("judgement of light",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("judgement of wisdom", name))
    {
        return new ActionNode ("judgement of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of light"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("divine shield", name))
    {
        return new ActionNode ("divine shield",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("divine protection"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("divine protection", name))
    {
        return new ActionNode ("divine protection",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("divine protection on party", name))
    {
        return new ActionNode ("divine protection on party",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("hammer of justice", name))
    {
        return new ActionNode ("hammer of justice",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("flash of light", name))
    {
        return new ActionNode ("flash of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("flash of light on party", name))
    {
        return new ActionNode ("flash of light on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light on party"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("holy light", name))
    {
        return new ActionNode ("holy light",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("holy light on party", name))
    {
        return new ActionNode ("holy light on party",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("lay on hands", name))
	{
		return new ActionNode ("lay on hands",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("lay on hands on party", name))
	{
		return new ActionNode ("lay on hands on party",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("judgement of justice", name))
	{
		return new ActionNode ("judgement of justice",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("hammer of wrath", name))
	{
		return new ActionNode ("hammer of wrath",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (!strcmp("holy shield", name))
    {
        return new ActionNode ("holy shield",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("hammer of the righteous", name))
    {
        return new ActionNode ("hammer of the righteous",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("holy wrath", name))
    {
        return new ActionNode ("holy wrath",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("consecration"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("blessing of kings", name))
    {
        return new ActionNode ("blessing of kings",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("retribution aura", name))
	{
		return new ActionNode ("retribution aura",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("shadow resistance aura", name))
	{
		return new ActionNode ("shadow resistance aura",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("frost resistance aura", name))
	{
		return new ActionNode ("frost resistance aura",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("fire resistance aura", name))
	{
		return new ActionNode ("fire resistance aura",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else return CombatStrategy::createAction(name);
}
