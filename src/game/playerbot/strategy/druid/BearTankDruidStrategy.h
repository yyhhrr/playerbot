#pragma once

#include "FeralDruidStrategy.h"

namespace ai
{
    class BearTankDruidStrategy : public FeralDruidStrategy
    {
    public:
        BearTankDruidStrategy(PlayerbotAI* ai) : FeralDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "bear"; }
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
		virtual StrategyType GetType() { return STRATEGY_TYPE_TANK; }
    };
}
