#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"

namespace ai
{
    class ChatCommandHandlerStrategy : public Strategy
    {
    public:
        ChatCommandHandlerStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "chat"; }
        virtual ActionNode* createAction(const char* name);
    };
}
