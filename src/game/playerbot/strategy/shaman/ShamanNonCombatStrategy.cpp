#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "ShamanNonCombatStrategy.h"

using namespace ai;

void ShamanNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("ancestral spirit", 23.0f), NULL)));
}

void ShamanNonCombatStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    CombatStrategy::InitMultipliers(multipliers);
}

ActionNode* ShamanNonCombatStrategy::GetAction(string name)
{
    ActionNode* node = CombatStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "strength of earth totem")
    {
        return new ActionNode ("strength of earth totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "flametongue totem")
    {
        return new ActionNode ("flametongue totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "windfury totem")
    {
        return new ActionNode ("windfury totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "mana spring totem")
    {
        return new ActionNode ("mana spring totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (name == "ancestral spirit")
	{
		return new ActionNode ("ancestral spirit",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else return CombatStrategy::GetAction(name);
}



