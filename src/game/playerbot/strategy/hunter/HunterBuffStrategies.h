#pragma once

#include "GenericHunterStrategy.h"
#include "../generic/GenericNonCombatStrategy.h"

namespace ai
{
    class HunterBuffSpeedStrategy : public GenericNonCombatStrategy
    {
    public:
        HunterBuffSpeedStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "bspeed"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class HunterBuffManaStrategy : public GenericNonCombatStrategy
    {
    public:
        HunterBuffManaStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "bmana"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

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
