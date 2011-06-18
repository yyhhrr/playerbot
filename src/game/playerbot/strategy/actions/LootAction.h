#pragma once

#include "../Action.h"
#include "../../LootObjectStack.h"
#include "MovementActions.h"

namespace ai
{
    class LootAction : public MovementAction {
    public:
        LootAction(PlayerbotAI* ai) : MovementAction(ai, "loot") { bot = ai->GetBot(); }
        virtual bool Execute(Event event);

    private:
        void DoLoot();
        void DoLoot(LootObject &lootObject);
        void AddMasterSelection();
        bool StoreLootItems(LootObject &lootObject, LootType lootType);
        void ReleaseLoot();
        Item* StoreItem(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem);
        void NotifyLootItemRemoved(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem );
        void StoreLootItem(LootObject &loot, uint32 lootIndex, LootType lootType);
        void DeactivateLootGameObject(LootObject &lootObject);
        bool IsLootAllowedBySkill(ItemPrototype const * proto);
        bool IsLootAllowed(LootItem * item);
        bool CheckSkill(uint32 lockId);
        bool CheckLevelBasedSkill(uint32 skill, int32 level);
 
    private:
        Player* bot;
    };

}