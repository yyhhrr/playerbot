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

ActionNode* HealPriestNonCombatStrategy::GetAction(string name)
{
    ActionNode* node = CombatStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "holy nova")
    {
        return new ActionNode ("holy nova",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    if (name == "power word: shield")
    {
        return new ActionNode ("power word: shield",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), NULL),
            /*C*/ NULL);
    }
    else if (name == "power word: shield on party")
    {
        return new ActionNode ("power word: shield on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), NULL),
            /*C*/ NULL);
    }
    else if (name == "renew")
    {
        return new ActionNode ("renew",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "renew on party")
    {
        return new ActionNode ("renew on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "greater heal")
    {
        return new ActionNode ("greater heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal"), NULL),
            /*C*/ NULL);
    }
    else if (name == "greater heal on party")
    {
        return new ActionNode ("greater heal on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("heal on party"), NULL),
            /*C*/ NULL);
    }
    else if (name == "heal")
    {
        return new ActionNode ("heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL),
            /*C*/ NULL);
    }
    else if (name == "heal on party")
    {
        return new ActionNode ("heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL),
            /*C*/ NULL);
    }
    else if (name == "lesser heal")
    {
        return new ActionNode ("lesser heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "lesser heal on party")
    {
        return new ActionNode ("lesser heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "flash heal")
    {
        return new ActionNode ("flash heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "flash heal on party")
    {
        return new ActionNode ("flash heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else return CombatStrategy::GetAction(name);
}



