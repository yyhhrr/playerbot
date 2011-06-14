#pragma once

#include "Action.h"

namespace ai
{
    class TellItemCountAction : public Action {
    public:
        TellItemCountAction(AiManagerRegistry* const ai) : Action(ai, "c") {}
        virtual bool Execute(Event event);
    };

}