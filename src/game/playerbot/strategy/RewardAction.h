#pragma once

#include "Action.h"
#include "InventoryAction.h"

namespace ai
{
    class RewardAction : public InventoryAction {
    public:
        RewardAction(AiManagerRegistry* const ai) : InventoryAction(ai, "reward") {}
        virtual bool Execute(Event event);


    };

}