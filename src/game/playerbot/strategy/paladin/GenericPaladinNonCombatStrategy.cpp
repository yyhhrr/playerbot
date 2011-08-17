#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "GenericPaladinNonCombatStrategy.h"

using namespace ai;

void GenericPaladinNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "blessing of kings on party",
        NextAction::array(0, new NextAction("blessing of kings on party", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("redemption", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"crusader aura",
		NextAction::array(0, new NextAction("crusader aura", 40.0f), NULL)));
}
