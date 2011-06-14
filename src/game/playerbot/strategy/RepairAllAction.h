#pragma once

#include "Action.h"

namespace ai
{
    class RepairAllAction : public Action 
    {
    public:
        RepairAllAction(AiManagerRegistry* const ai) : Action(ai, "repair") {}
        virtual bool Execute(Event event);
    };
}