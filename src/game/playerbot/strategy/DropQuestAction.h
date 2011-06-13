#pragma once

#include "Action.h"

namespace ai
{
    class DropQuestAction : public Action {
    public:
        DropQuestAction(AiManagerRegistry* const ai) : Action(ai, "drop quest") {}
        virtual bool Execute(Event event);
    };

}