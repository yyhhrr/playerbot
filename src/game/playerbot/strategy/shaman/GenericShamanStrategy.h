#pragma once

#include "../Strategy.h"

namespace ai
{
    class GenericShamanStrategy : public CombatStrategy
    {
    public:
        GenericShamanStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual ActionNode* GetAction(const char* name);

    };
}