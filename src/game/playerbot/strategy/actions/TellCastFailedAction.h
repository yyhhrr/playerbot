#pragma once

#include "../Action.h"

namespace ai
{
    class TellCastFailedAction : public Action 
    {
    public:
        TellCastFailedAction(PlayerbotAI* ai) : Action(ai, "tell cast failed") {}
        virtual bool Execute(Event event);
    };
}