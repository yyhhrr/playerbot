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

ActionNode* ShamanNonCombatStrategy::GetAction(const char* name)
{
    ActionNode* node = CombatStrategy::GetAction(name);
    if (node)
        return node;

    if (!strcmp("strength of earth totem", name))
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
	else if (!strcmp("ancestral spirit", name))
	{
		return new ActionNode ("ancestral spirit",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else return CombatStrategy::GetAction(name);
}



