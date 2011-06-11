#pragma once

#include "GenericDruidStrategy.h"
#include "DruidAiObjectContext.h"

namespace ai
{
    class FeralDruidStrategy : public GenericDruidStrategy
    {
    protected:
        FeralDruidStrategy(AiManagerRegistry* const ai) : GenericDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(const char* name);
    };

}