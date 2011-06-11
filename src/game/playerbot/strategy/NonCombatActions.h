#pragma once

#include "Action.h"

namespace ai
{
    class DrinkAction : public Action {
    public:
        DrinkAction(AiManagerRegistry* const ai) : Action(ai, "drink") {}
        virtual bool Execute(Event event) {
            ai->GetInventoryManager()->UseDrink();
            return true;
        }
        virtual bool isUseful() {
            return ai->GetStatsManager()->GetManaPercent(ai->GetTargetManager()->GetSelf()) < LOW_HEALTH_PERCENT && ai->GetInventoryManager()->HasDrink();
        }
    };

    class EatAction : public Action {
    public:
        EatAction(AiManagerRegistry* const ai) : Action(ai, "eat") {}
        virtual bool Execute(Event event) {
            ai->GetInventoryManager()->UseFood();
            return true;
        }
        virtual bool isUseful() {
            return ai->GetStatsManager()->GetHealthPercent(ai->GetTargetManager()->GetSelf()) < LOW_HEALTH_PERCENT && 
				ai->GetInventoryManager()->HasFood();
        }
    };

}