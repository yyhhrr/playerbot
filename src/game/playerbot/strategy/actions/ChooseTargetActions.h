#pragma once

#include "../Action.h"
#include "AttackAction.h"

namespace ai
{
    class DpsAssistAction : public AttackAction {
    public:
        DpsAssistAction(PlayerbotAI* ai) : AttackAction(ai, "dps assist") {}
        
        virtual string GetTargetName() { return "dps target"; }
    };   
    
    class TankAssistAction : public AttackAction {
    public:
        TankAssistAction(PlayerbotAI* ai) : AttackAction(ai, "tank assist") {}
        virtual string GetTargetName() { return "tank target"; }
    };   
  
    class AttackAnythingAction : public AttackAction {
    public:
        AttackAnythingAction(PlayerbotAI* ai) : AttackAction(ai, "attack anything") {}
        virtual string GetTargetName() { return "grind target"; }
    };   
   
}
