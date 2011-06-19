#pragma once

#include "GenericDruidStrategy.h"
#include "DruidAiObjectContext.h"

namespace ai
{
    class FeralDruidStrategy : public GenericDruidStrategy
    {
    protected:
        FeralDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
    };

}