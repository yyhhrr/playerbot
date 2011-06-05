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
        virtual void Execute() {
            ai->GetMoveManager()->Attack(ai->GetTargetManager()->GetCurrentTarget());
        }
    };

    class UseHealingPotion : public Action {
    public:
        UseHealingPotion(AiManagerRegistry* const ai) : Action(ai, "healing potion") {}
        virtual void Execute() {
            ai->GetInventoryManager()->UseHealingPotion(); 
        }
        virtual bool isPossible() {
            return ai->GetInventoryManager()->HasHealingPotion();
        }
    };

    class UseManaPotion : public Action {
    public:
        UseManaPotion(AiManagerRegistry* const ai) : Action(ai, "mana potion") {}
        virtual void Execute() {
            ai->GetInventoryManager()->UseManaPotion(); 
        }
        virtual bool isPossible() {
            return ai->GetInventoryManager()->HasManaPotion();
        }
    };

    class UsePanicPotion : public Action {
    public:
        UsePanicPotion(AiManagerRegistry* const ai) : Action(ai, "panic potion") {}
        virtual void Execute() {
            ai->GetInventoryManager()->UsePanicPotion(); 
        }
        virtual bool isPossible() {
            return ai->GetInventoryManager()->HasPanicPotion();
        }
    };

	class UseItemAction : public Action {
	public:
		UseItemAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
		virtual void Execute() {
			ai->GetInventoryManager()->FindAndUse(getName()); 
		}
        virtual bool isUseful();
		virtual bool isPossible() {
			return ai->GetInventoryManager()->GetItemCount(getName()) > 0;
		}
	};

    class LootAction : public Action {
    public:
        LootAction(AiManagerRegistry* const ai) : Action(ai, "loot") {}
        virtual void Execute() {
            ai->GetInventoryManager()->DoLoot();
        }
    };

    class LootAllAction : public Action {
    public:
        LootAllAction(AiManagerRegistry* const ai) : Action(ai, "loot all") {}
        virtual void Execute() {
			AiInventoryManager* manager = ai->GetInventoryManager();
			manager->AddAllLoot();
            manager->DoLoot();
        }
    };

    class EmoteAction : public Action
    {
    public:
        EmoteAction(AiManagerRegistry* const ai, uint32 type) : Action(ai, "emote") {
            this->type = type;
        }

        virtual void Execute() {
            ai->GetSocialManager()->Emote(type ? type : rand() % 450);
        }

    protected:
        uint32 type;
    };
    
    class ChangeCombatStrategyAction : public Action {
    public:
        ChangeCombatStrategyAction(AiManagerRegistry* const ai, const char* name);
        virtual void Execute();

    private:
        string name;
    };
}