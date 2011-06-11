#pragma once

#include "../Strategy.h"

namespace ai
{
    class AiObjectContext;

    class GenericHunterStrategy : public CombatStrategy
    {
    public:
        GenericHunterStrategy(AiManagerRegistry* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual AiObjectContext* createAiObjectContext();
        virtual const char* getName() { return "hunter"; }
        virtual ActionNode* GetAction(const char* name);
    };
}

