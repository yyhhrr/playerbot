#pragma once

#include "../Strategy.h"

namespace ai
{
    class HealPriestNonCombatStrategy : public CombatStrategy
    {
    public:
        HealPriestNonCombatStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "nc"; }
        virtual ActionNode* GetAction(string name);

    };
}