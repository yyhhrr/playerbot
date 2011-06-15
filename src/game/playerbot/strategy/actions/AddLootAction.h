#pragma once

#include "../Action.h"

namespace ai
{
    class AddLootAction : public Action {
    public:
        AddLootAction(PlayerbotAI* ai) : Action(ai, "add loot") {}
        virtual bool Execute(Event event);

   
    };

    class AddAllLootAction : public Action {
    public:
        AddAllLootAction(PlayerbotAI* ai) : Action(ai, "add all loot") {}
        virtual bool Execute(Event event);


    };

}