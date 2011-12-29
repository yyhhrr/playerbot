#include "../../pchdef.h"
#include "../playerbot.h"
#include "GenericNonCombatStrategy.h"
#include "PassiveMultiplier.h"
#include "LowManaMultiplier.h"

using namespace ai;

void UseFoodStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    Strategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("stay", 9.0f), new NextAction("food", 9.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("stay", 9.0f), new NextAction("drink", 9.0f), NULL)));
}


void TankAssistStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no attackers",
        NextAction::array(0, new NextAction("tank assist", 50.0f), NULL)));
}

void TankAoeStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"tank aoe",
		NextAction::array(0, new NextAction("tank assist", 50.0f), NULL)));
}

void DpsAssistStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no attackers",
        NextAction::array(0, new NextAction("dps assist", 50.0f), NULL)));
}

void DpsAoeStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"timer",
		NextAction::array(0, new NextAction("dps assist", 50.0f), NULL)));
}

void AttackWeakStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"not least hp target active",
		NextAction::array(0, new NextAction("attack least hp target", 60.0f), NULL)));
}

void AttackRtiStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"no attackers",
		NextAction::array(0, new NextAction("attack rti target", 60.0f), NULL)));
}

NextAction** GrindingStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("add all loot", 5.0f), NULL);
}

void GrindingStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no target",
        NextAction::array(0, new NextAction("attack anything", 5.0f), NULL)));
}

NextAction** StayNonCombatStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("stay", 1.0f), NULL);
}

NextAction** FollowMasterNonCombatStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("follow master", 1.0f), NULL);
}

void FollowMasterNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "out of react range",
        NextAction::array(0, new NextAction("tell out of react range", 10.0f), NULL)));
}

NextAction** FollowLineNonCombatStrategy::getDefaultActions()
{
	return NextAction::array(0, new NextAction("follow line", 1.0f), NULL);
}

NextAction** StayCircleStrategy::getDefaultActions()
{
	return NextAction::array(0, new NextAction("stay circle", 50.0f), NULL);
}

NextAction** StayLineStrategy::getDefaultActions()
{
	return NextAction::array(0, new NextAction("stay line", 50.0f), NULL);
}

NextAction** StayCombatStrategy::getDefaultActions()
{
	return NextAction::array(0, new NextAction("stay combat", 1.0f), NULL);
}


NextAction** GoAwayStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("goaway", 50.0f), NULL);
}

void GoAwayStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy too close",
        NextAction::array(0, new NextAction("goaway", 50.0f), NULL)));
}

void RandomEmoteStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("emote", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "seldom",
        NextAction::array(0, new NextAction("suggest what to do", 1.0f), NULL)));
}

void PassiveStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new PassiveMultiplier());
}

void LowManaStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new LowManaMultiplier());
}

void FollowMasterRandomStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "far from master",
        NextAction::array(0, new NextAction("be near", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("move random", 2.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "target in sight",
        NextAction::array(0, new NextAction("stay combat",3.0f), NULL)));
}
