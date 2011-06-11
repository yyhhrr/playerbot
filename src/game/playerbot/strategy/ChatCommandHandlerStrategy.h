#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"
#include "PassTroughStrategy.h"

namespace ai
{
    class ChatCommandHandlerStrategy : public PassTroughStrategy
    {
    public:
        ChatCommandHandlerStrategy(AiManagerRegistry* const ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "chat"; }
    };
}
