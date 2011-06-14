#pragma once

#include "Action.h"
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"

namespace ai
{
    class MeleeAction : public AttackAction 
    {
    public:
        MeleeAction(AiManagerRegistry* const ai) : AttackAction(ai, "melee") {}

        virtual const char* GetTargetName() { return "current target"; }
    };

    class UseHealingPotion : public Action {
    public:
        UseHealingPotion(AiManagerRegistry* const ai) : Action(ai, "healing potion") {}
        virtual bool Execute(Event event) 
        {
            ai->GetInventoryManager()->UseHealingPotion(); 
            return true;
        }
        virtual bool isPossible() 
        {
            return ai->GetInventoryManager()->HasHealingPotion();
        }
    };

    class UseManaPotion : public Action 
    {
    public:
        UseManaPotion(AiManagerRegistry* const ai) : Action(ai, "mana potion") {}
        virtual bool Execute(Event event) 
        {
            ai->GetInventoryManager()->UseManaPotion(); 
            return true;
        }
        virtual bool isPossible() 
        {
            return ai->GetInventoryManager()->HasManaPotion();
        }
    };

    class UsePanicPotion : public Action 
    {
    public:
        UsePanicPotion(AiManagerRegistry* const ai) : Action(ai, "panic potion") {}
        virtual bool Execute(Event event) 
        {
            ai->GetInventoryManager()->UsePanicPotion(); 
            return true;
        }
        virtual bool isPossible() 
        {
            return ai->GetInventoryManager()->HasPanicPotion();
        }
    };

	class UseItemAction : public Action 
    {
	public:
		UseItemAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
		virtual bool Execute(Event event) 
        {
			ai->GetInventoryManager()->FindAndUse(getName()); 
            return true;
		}
        virtual bool isUseful();
		virtual bool isPossible() 
        {
			return AI_VALUE2(uint8, "item count", getName()) > 0;
		}
	};

    class ChangeCombatStrategyAction : public Action 
    {
    public:
        ChangeCombatStrategyAction(AiManagerRegistry* const ai, const char* name);
        virtual bool Execute(Event event);

    private:
        string name;
    };
}