#pragma once

#include "HealPriestStrategy.h"

namespace ai
{
    class DpsPriestStrategy : public GenericPriestStrategy
    {
    public:
        DpsPriestStrategy(PlayerbotAI* ai);

    public:
        virtual NextAction** getDefaultActions();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps"; }
        virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }
    };
}
