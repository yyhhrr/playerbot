#pragma once

#include "../Strategy.h"
#include "PaladinAiObjectContext.h"

namespace ai
{
    class GenericPaladinStrategy : public CombatStrategy
    {
    public:
        GenericPaladinStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "paladin"; }
        ActionNode* GetAction(string name);
    };
}
