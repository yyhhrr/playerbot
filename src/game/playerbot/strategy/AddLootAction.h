#pragma once

#include "Action.h"

namespace ai
{
    class AddLootAction : public Action {
    public:
        AddLootAction(AiManagerRegistry* const ai) : Action(ai, "add loot") {}
        virtual bool Execute(Event event);

   
    };

    class AddAllLootAction : public Action {
    public:
        AddAllLootAction(AiManagerRegistry* const ai) : Action(ai, "add all loot") {}
        virtual bool Execute(Event event);


    };

}