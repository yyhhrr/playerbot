#pragma once

#include "GenericPaladinStrategy.h"

namespace ai
{
    class DpsPaladinStrategy : public GenericPaladinStrategy
    {
    public:
        DpsPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "dps"; }
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-tank"; }
    };
}