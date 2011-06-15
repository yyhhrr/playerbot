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
        virtual const char* getName() { return "warrior"; }
        ActionNode* GetAction(const char* name);
    };
}