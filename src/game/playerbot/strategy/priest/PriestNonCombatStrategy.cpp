#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "PriestNonCombatStrategy.h"
#include "PriestNonCombatStrategyActionNodeFactory.h"

using namespace ai;

PriestNonCombatStrategy::PriestNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new PriestNonCombatStrategyActionNodeFactory());
}

void PriestNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "power word: fortitude",
        NextAction::array(0, new NextAction("power word: fortitude", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party",
        NextAction::array(0, new NextAction("power word: fortitude on party", 20.0f), NULL)));


    triggers.push_back(new TriggerNode(
        "divine spirit",
        NextAction::array(0, new NextAction("divine spirit", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party",
        NextAction::array(0, new NextAction("divine spirit on party", 21.0f), NULL)));


    triggers.push_back(new TriggerNode(
        "inner fire",
        NextAction::array(0, new NextAction("inner fire", 19.0f), NULL)));


    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("greater heal", 70.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("greater heal on party", 60.0f), NULL)));

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
