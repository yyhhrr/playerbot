#pragma once

#include "GenericHunterStrategy.h"
#include "../GenericNonCombatStrategy.h"

namespace ai
{
	class HunterBuffDpsStrategy : public GenericNonCombatStrategy
	{
	public:
		HunterBuffDpsStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "bdps"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

	class HunterNatureResistanceStrategy : public GenericNonCombatStrategy
	{
	public:
		HunterNatureResistanceStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "rnature"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};
}
