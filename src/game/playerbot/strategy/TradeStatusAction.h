#pragma once

#include "Action.h"
#include "InventoryAction.h"

namespace ai
{
    class TradeStatusAction : public InventoryAction 
    {
    public:
        TradeStatusAction(AiManagerRegistry* const ai) : InventoryAction(ai, "accept trade") {}
        virtual bool Execute(Event event);

    private:
        void BeginTrade();
    };
}