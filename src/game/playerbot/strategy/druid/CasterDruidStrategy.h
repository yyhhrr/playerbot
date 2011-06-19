#pragma once

#include "GenericDruidStrategy.h"

namespace ai
{
    class CasterDruidStrategy : public GenericDruidStrategy
    {
    public:
        CasterDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "caster"; }
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-cat,-bear"; }
    };
}