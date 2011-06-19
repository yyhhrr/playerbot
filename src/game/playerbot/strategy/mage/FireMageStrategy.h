#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FireMageStrategy : public GenericMageStrategy
    {
    public:
        FireMageStrategy(PlayerbotAI* ai) : GenericMageStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "fire"; }
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-frost"; }
    };
}