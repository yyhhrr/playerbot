#pragma once

#include "../Strategy.h"

namespace ai
{
    class GenericPriestStrategy : public CombatStrategy
    {
    public:
        GenericPriestStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual ActionNode* GetAction(string name);

    };
}