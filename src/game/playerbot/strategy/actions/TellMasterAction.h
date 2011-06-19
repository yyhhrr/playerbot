#pragma once

#include "../Action.h"

namespace ai
{
    class TellMasterAction : public Action {
    public:
        TellMasterAction(PlayerbotAI* ai, string text) : Action(ai, "tell master"), text(text) {}

        virtual bool Execute(Event event)
        {
            ai->TellMaster(text);
            return true;
        }

    private:
        string text;
    };

}