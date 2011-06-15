#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FrostMageStrategy : public GenericMageStrategy
    {
    public:
        FrostMageStrategy(PlayerbotAI* ai) : GenericMageStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "frost"; }
        virtual ActionNode* GetAction(const char* name);
        virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-fire"; }
    };
}