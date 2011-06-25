#pragma once

#include "../Action.h"
#include "../../LootObjectStack.h"
#include "MovementActions.h"

namespace ai
{
    class LootAction : public MovementAction 
    {
    public:
        LootAction(PlayerbotAI* ai) : MovementAction(ai, "loot") {}
        virtual bool Execute(Event event);
    };
    
    class OpenLootAction : public MovementAction 
    {
    public:
        OpenLootAction(PlayerbotAI* ai) : MovementAction(ai, "open loot") {}
        virtual bool Execute(Event event);

    private:
        bool DoLoot(LootObject& lootObject);
    };

    class StoreLootAction : public MovementAction 
    {
    public:
        StoreLootAction(PlayerbotAI* ai) : MovementAction(ai, "store loot") {}
        virtual bool Execute(Event event);

    private:
        bool IsLootAllowed(uint32 itemid);
        bool IsLootAllowedBySkill(ItemPrototype const * proto);
    };
}