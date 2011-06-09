#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"

using namespace ai;

void GenericShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "windfury totem",
        NextAction::array(0, new NextAction("windfury totem", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mana spring totem",
        NextAction::array(0, new NextAction("mana spring totem", 16.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "flametongue totem",
        NextAction::array(0, new NextAction("flametongue totem", 17.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "strength of earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear",
        NextAction::array(0, new NextAction("wind shear", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "purge",
		NextAction::array(0, new NextAction("purge", 10.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0, new NextAction("chain heal on party", 25.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0, new NextAction("riptide on party", 25.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium health",
		NextAction::array(0, new NextAction("chain heal", 26.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"low health",
		NextAction::array(0, new NextAction("riptide", 26.0f), NULL)));
}

void GenericShamanStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* GenericShamanStrategy::createAction(const char* name)
{
    ActionNode* node = CombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("water shield", name))
    {
        return new ActionNode ("water shield",
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
    else if (!strcmp("strength of earth totem", name))
    {
        return new ActionNode ("strength of earth totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("flametongue totem", name))
    {
        return new ActionNode ("flametongue totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("windfury totem", name))
    {
        return new ActionNode ("windfury totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("mana spring totem", name))
    {
        return new ActionNode ("mana spring totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (!strcmp("mana tide totem", name))
	{
		return new ActionNode ("mana tide totem",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("healing stream totem", name))
	{
		return new ActionNode ("healing stream totem",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (!strcmp("wind shear", name))
    {
        return new ActionNode ("wind shear",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("rockbiter weapon", name))
    {
        return new ActionNode ("rockbiter weapon",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("flametongue weapon", name))
    {
        return new ActionNode ("flametongue weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbrand weapon"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("frostbrand weapon", name))
    {
        return new ActionNode ("frostbrand weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("windfury weapon", name))
    {
        return new ActionNode ("windfury weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
	else if (!strcmp("purge", name))
	{
		return new ActionNode ("purge",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("healing wave", name))
	{
		return new ActionNode ("healing wave",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("lesser healing wave", name))
	{
		return new ActionNode ("lesser healing wave",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("healing wave on party", name))
	{
		return new ActionNode ("healing wave on party",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("lesser healing wave on party", name))
	{
		return new ActionNode ("lesser healing wave on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("earth shield", name))
	{
		return new ActionNode ("earth shield",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("earth shield on party", name))
	{
		return new ActionNode ("earth shield on party",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (!strcmp("chain heal", name))
	{
		return new ActionNode ("chain heal",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("lesser healing wave"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("riptide", name))
	{
		return new ActionNode ("riptide",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("chain heal on party", name))
	{
		return new ActionNode ("chain heal on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("lesser healing wave on party"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("riptide on party", name))
	{
		return new ActionNode ("riptide on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
			/*C*/ NULL);
	}
    return CombatStrategy::createAction(name);
}



