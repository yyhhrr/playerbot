#pragma once

#include "Action.h"
#include "InventoryAction.h"

namespace ai
{
    class TellItemCountAction : public InventoryAction {
    public:
        TellItemCountAction(AiManagerRegistry* const ai) : InventoryAction(ai, "c") {}
        virtual bool Execute(Event event);
    };

}