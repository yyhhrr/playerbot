#pragma once

#include "GenericPaladinStrategy.h"

namespace ai
{
    class TankPaladinStrategy : public GenericPaladinStrategy
    {
    public:
        TankPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai) {}
    
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