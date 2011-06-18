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
        "low health", 
        NextAction::array(0, new NextAction("food", 9.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        "low mana", 
        NextAction::array(0, new NextAction("drink", 9.0f), NULL)));
}

void LootNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "loot available", 
        NextAction::array(0, new NextAction("loot", 2.0f), NULL)));
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

NextAction** GrindingStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("loot all", 1.0f), NULL);
}

void GrindingStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no target", 
        NextAction::array(0, new NextAction("attack anything", 1.0f), NULL)));
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
}

NextAction** FollowLineNonCombatStrategy::getDefaultActions()
{
	return NextAction::array(0, new NextAction("follow line", 1.0f), NULL);
}


NextAction** GoAwayNonCombatStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("goaway", 1.0f), NULL);
}

void RandomEmoteStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "random", 
        NextAction::array(0, new NextAction("emote", 1.0f), NULL)));
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
        NextAction::array(0, new NextAction("follow master random", 1.0f), NULL)));
}
