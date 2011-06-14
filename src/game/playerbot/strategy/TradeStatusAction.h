#pragma once

#include "Action.h"

namespace ai
{
    class TradeStatusAction : public Action 
    {
    public:
        TradeStatusAction(AiManagerRegistry* const ai) : Action(ai, "accept trade") {}
        virtual bool Execute(Event event);

    private:
        void BeginTrade();
    };
}