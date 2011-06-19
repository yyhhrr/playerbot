#pragma once

#include "../Strategy.h"

namespace ai
{
    class DpsRogueStrategy : public CombatStrategy
    {
    public:
        DpsRogueStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "dps"; }
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
    };
}