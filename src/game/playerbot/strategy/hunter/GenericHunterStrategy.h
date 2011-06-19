#pragma once

#include "../Strategy.h"

namespace ai
{
    class AiObjectContext;

    class GenericHunterStrategy : public CombatStrategy
    {
    public:
        GenericHunterStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual AiObjectContext* createAiObjectContext();
        virtual string getName() { return "hunter"; }
        virtual ActionNode* GetAction(string name);
    };
}

