#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"
#include "PassTroughStrategy.h"

namespace ai
{
    class DeadStrategy : public PassTroughStrategy
    {
    public:
        DeadStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "dead"; }
    };
}
