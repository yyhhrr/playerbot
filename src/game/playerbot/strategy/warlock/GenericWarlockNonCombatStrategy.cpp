#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockNonCombatStrategy.h"

using namespace ai;

void GenericWarlockNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("demon armor", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no healthstone",
		NextAction::array(0, new NextAction("create healthstone", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no firestone",
		NextAction::array(0, new NextAction("create firestone", 14.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no spellstone",
		NextAction::array(0, new NextAction("create spellstone", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "spellstone",
        NextAction::array(0, new NextAction("spellstone", 13.0f), NULL)));
}


ActionNode* GenericWarlockNonCombatStrategy::GetAction(string name)
{
    ActionNode* node = GenericNonCombatStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "demon armor")
    {
        return new ActionNode ("demon armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("demon skin"), NULL),
            /*C*/ NULL);
    }
    else return GenericNonCombatStrategy::GetAction(name);
}
