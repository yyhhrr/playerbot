#pragma once

#include "Action.h"
#include "UseItemAction.h"

namespace ai
{
    class DrinkAction : public UseItemAction 
    {
    public:
        DrinkAction(PlayerbotAI* ai) : UseItemAction(ai, "drink") {}
        
        virtual bool isUseful() 
        {
            return UseItemAction::isUseful() && AI_VALUE2(uint8, "mana", "self target") < LOW_HEALTH_PERCENT;
        }
    };

    class EatAction : public UseItemAction 
    {
    public:
        EatAction(PlayerbotAI* ai) : UseItemAction(ai, "food") {}

        virtual bool isUseful() 
        {
            return UseItemAction::isUseful() && AI_VALUE2(uint8, "health", "self target") < LOW_HEALTH_PERCENT;
        }
    };

}