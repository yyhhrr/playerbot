#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "PaladinBuffStrategies.h"
#include "PaladinActions.h"

using namespace ai;

void PaladinBuffManaStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of wisdom", 24.0f), NULL)));
}

void PaladinBuffHealthStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of light", 24.0f), NULL)));
}

void PaladinBuffDpsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of command", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new RetributionAuraTrigger(ai), 
		NextAction::array(0, new NextAction("retribution aura", 25.0f), NULL)));
}

void PaladinShadowResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new ShadowResistanceAuraTrigger(ai), 
		NextAction::array(0, new NextAction("shadow resistance aura", 24.0f), NULL)));
}

void PaladinFrostResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new FrostResistanceAuraTrigger(ai), 
		NextAction::array(0, new NextAction("frost resistance aura", 24.0f), NULL)));
}

void PaladinFireResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new FireResistanceAuraTrigger(ai), 
		NextAction::array(0, new NextAction("fire resistance aura", 24.0f), NULL)));
}


void PaladinBuffArmorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new DevotionAuraTrigger(ai), 
		NextAction::array(0, new NextAction("devotion aura", 25.0f), NULL)));
}

