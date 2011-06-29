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

ActionNode* GenericShamanStrategy::GetAction(string name)
{
    ActionNode* node = CombatStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "flametongue weapon")
    {
        return new ActionNode ("flametongue weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbrand weapon"), NULL),
            /*C*/ NULL);
    }
    else if (name == "frostbrand weapon")
    {
        return new ActionNode ("frostbrand weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
    else if (name == "windfury weapon")
    {
        return new ActionNode ("windfury weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
	else if (name == "lesser healing wave")
	{
		return new ActionNode ("lesser healing wave",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
			/*C*/ NULL);
	}
	else if (name == "lesser healing wave on party")
	{
		return new ActionNode ("lesser healing wave on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
			/*C*/ NULL);
	}
	else if (name == "chain heal")
	{
		return new ActionNode ("chain heal",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("lesser healing wave"), NULL),
			/*C*/ NULL);
	}
	else if (name == "riptide")
	{
		return new ActionNode ("riptide",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
			/*C*/ NULL);
	}
	else if (name == "chain heal on party")
	{
		return new ActionNode ("chain heal on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("lesser healing wave on party"), NULL),
			/*C*/ NULL);
	}
	else if (name == "riptide on party")
	{
		return new ActionNode ("riptide on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
			/*C*/ NULL);
	}
    return CombatStrategy::GetAction(name);
}



