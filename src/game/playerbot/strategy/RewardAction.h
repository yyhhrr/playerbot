#pragma once

#include "Action.h"
#include "InventoryAction.h"

namespace ai
{
    class RewardAction : public InventoryAction {
    public:
        RewardAction(PlayerbotAI* ai) : InventoryAction(ai, "reward") {}
        virtual bool Execute(Event event);


    };

}