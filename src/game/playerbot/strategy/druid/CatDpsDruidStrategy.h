#pragma once

#include "FeralDruidStrategy.h"

namespace ai
{
    class CatDpsDruidStrategy : public FeralDruidStrategy
    {
    public:
        CatDpsDruidStrategy(PlayerbotAI* ai) : FeralDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "cat"; }
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
    };
}
