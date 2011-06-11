#pragma once

#include "GenericShamanStrategy.h"

namespace ai
{
    class HealShamanStrategy : public GenericShamanStrategy
    {
    public:
        HealShamanStrategy(AiManagerRegistry* const ai) : GenericShamanStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
        virtual const char* getName() { return "heal"; }
        virtual ActionNode* GetAction(const char* name);
		virtual string GetIncompatibleStrategies() { return "-dps"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_HEAL; }
    };
}
