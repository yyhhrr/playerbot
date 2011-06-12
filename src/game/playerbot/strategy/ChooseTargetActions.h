#pragma once

#include "Action.h"

namespace ai
{
    class AttackAction : public Action {
    public:
        AttackAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
        
		virtual bool isPossible() { return GetTarget(); }

        virtual bool Execute(Event event) 
        {
            Unit* target = GetTarget();
            if (target)
                ai->GetMoveManager()->Attack(target);
            
            return true;
        }
    };   

    class DpsAssistAction : public AttackAction {
    public:
        DpsAssistAction(AiManagerRegistry* const ai) : AttackAction(ai, "dps assist") {}
        
        virtual const char* GetTargetName() { return "dps target"; }
    };   
    
    class TankAssistAction : public AttackAction {
    public:
        TankAssistAction(AiManagerRegistry* const ai) : AttackAction(ai, "tank assist") {}
        virtual const char* GetTargetName() { return "tank target"; }
    };   
  
    class AttackAnythingAction : public AttackAction {
    public:
        AttackAnythingAction(AiManagerRegistry* const ai) : AttackAction(ai, "attack anything") {}
        virtual const char* GetTargetName() { return "grind target"; }
    };   
   
}
