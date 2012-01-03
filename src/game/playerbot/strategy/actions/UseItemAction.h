#pragma once

#include "../Action.h"

namespace ai
{
	class UseItemAction : public Action {
	public:
		UseItemAction(PlayerbotAI* ai, string name = "use") : Action(ai, name) {}

    public:
        virtual bool Execute(Event event);
        virtual bool isPossible();

    private:
        bool UseItem(Item* item, ObjectGuid go = ObjectGuid());
        void UseGameObject(ObjectGuid guid);
    };

    class UseSpellItemAction : public UseItemAction {
    public:
        UseSpellItemAction(PlayerbotAI* ai, string name) : UseItemAction(ai, name) {}

    public:
        virtual bool isUseful();
    };

    class UseHealingPotion : public UseItemAction {
    public:
        UseHealingPotion(PlayerbotAI* ai) : UseItemAction(ai, "healing potion") {}
    };

    class UseManaPotion : public UseItemAction
    {
    public:
        UseManaPotion(PlayerbotAI* ai) : UseItemAction(ai, "mana potion") {}
    };
}
