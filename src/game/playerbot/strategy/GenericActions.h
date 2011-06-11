#pragma once

#include "Action.h"
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"

namespace ai
{
    class MeleeAction : public Action {
    public:
        MeleeAction(AiManagerRegistry* const ai) : Action(ai, "melee") {}
        virtual bool Execute(Event event) {
            ai->GetMoveManager()->Attack(ai->GetTargetManager()->GetCurrentTarget());
            return true;
        }
    };

    class UseHealingPotion : public Action {
    public:
        UseHealingPotion(AiManagerRegistry* const ai) : Action(ai, "healing potion") {}
        virtual bool Execute(Event event) {
            ai->GetInventoryManager()->UseHealingPotion(); 
            return true;
        }
        virtual bool isPossible() {
            return ai->GetInventoryManager()->HasHealingPotion();
        }
    };

    class UseManaPotion : public Action {
    public:
        UseManaPotion(AiManagerRegistry* const ai) : Action(ai, "mana potion") {}
        virtual bool Execute(Event event) {
            ai->GetInventoryManager()->UseManaPotion(); 
            return true;
        }
        virtual bool isPossible() {
            return ai->GetInventoryManager()->HasManaPotion();
        }
    };

    class UsePanicPotion : public Action {
    public:
        UsePanicPotion(AiManagerRegistry* const ai) : Action(ai, "panic potion") {}
        virtual bool Execute(Event event) {
            ai->GetInventoryManager()->UsePanicPotion(); 
            return true;
        }
        virtual bool isPossible() {
            return ai->GetInventoryManager()->HasPanicPotion();
        }
    };

	class UseItemAction : public Action {
	public:
		UseItemAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
		virtual bool Execute(Event event) {
			ai->GetInventoryManager()->FindAndUse(getName()); 
            return true;
		}
        virtual bool isUseful();
		virtual bool isPossible() {
			return ai->GetInventoryManager()->GetItemCount(getName()) > 0;
		}
	};

    class LootAction : public Action {
    public:
        LootAction(AiManagerRegistry* const ai) : Action(ai, "loot") {}
        virtual bool Execute(Event event) {
            ai->GetInventoryManager()->DoLoot();
            return true;
        }
    };

    class LootAllAction : public Action {
    public:
        LootAllAction(AiManagerRegistry* const ai) : Action(ai, "loot all") {}
        virtual bool Execute(Event event) {
			AiInventoryManager* manager = ai->GetInventoryManager();
			manager->AddAllLoot();
            manager->DoLoot();
            return true;
        }
    };
    
    class ChangeCombatStrategyAction : public Action {
    public:
        ChangeCombatStrategyAction(AiManagerRegistry* const ai, const char* name);
        virtual bool Execute(Event event);

    private:
        string name;
    };
}