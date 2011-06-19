#pragma once

#include "../Strategy.h"

namespace ai
{
    class AiObjectContext;

    class GenericWarriorStrategy : public CombatStrategy
    {
    public:
        GenericWarriorStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual AiObjectContext* createAiObjectContext();
        virtual string getName() { return "warrior"; }
        ActionNode* GetAction(string name);
    };
}