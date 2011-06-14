#pragma once

#include "Action.h"
#include "InventoryAction.h"

namespace ai
{
    class TradeAction : public InventoryAction {
    public:
        TradeAction(AiManagerRegistry* const ai) : InventoryAction(ai, "trade") {}
        virtual bool Execute(Event event);

    private:
        bool TradeItem(FindItemVisitor *visitor, int8 slot);
        bool TradeItem(const Item& item, int8 slot);

    };

}