#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "GenericMageNonCombatStrategy.h"

using namespace ai;

void GenericMageNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane intellect",
        NextAction::array(0, new NextAction("arcane intellect", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane intellect on party",
        NextAction::array(0, new NextAction("arcane intellect on party", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no drink",
		NextAction::array(0, new NextAction("conjure water", 16.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no food",
		NextAction::array(0, new NextAction("conjure food", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", 19.0f), NULL)));
}


ActionNode* GenericMageNonCombatStrategy::GetAction(string name)
{
    ActionNode* node = GenericMageStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "mage armor")
    {
        return new ActionNode ("mage armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("ice armor"), NULL),
            /*C*/ NULL);
    }
    else if (name == "ice armor")
    {
        return new ActionNode ("ice armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frost armor"), NULL),
            /*C*/ NULL);
    }

    return GenericMageStrategy::GetAction(name);
}
