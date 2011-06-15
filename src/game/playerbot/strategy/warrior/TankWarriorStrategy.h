#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class TankWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        TankWarriorStrategy(PlayerbotAI* ai) : GenericWarriorStrategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "tank"; }
        virtual ActionNode* GetAction(const char* name);
        virtual NextAction** getDefaultActions();
		virtual StrategyType GetType() { return STRATEGY_TYPE_TANK; }
		virtual string GetIncompatibleStrategies() { return "-dps"; }
    };
}