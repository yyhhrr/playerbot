#pragma once

#include "Action.h"
#include "AttackAction.h"

namespace ai
{
    class DpsAssistAction : public AttackAction {
    public:
        DpsAssistAction(PlayerbotAI* ai) : AttackAction(ai, "dps assist") {}
        
        virtual const char* GetTargetName() { return "dps target"; }
    };   
    
    class TankAssistAction : public AttackAction {
    public:
        TankAssistAction(PlayerbotAI* ai) : AttackAction(ai, "tank assist") {}
        virtual const char* GetTargetName() { return "tank target"; }
    };   
  
    class AttackAnythingAction : public AttackAction {
    public:
        AttackAnythingAction(PlayerbotAI* ai) : AttackAction(ai, "attack anything") {}
        virtual const char* GetTargetName() { return "grind target"; }
    };   
   
}
