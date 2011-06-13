#pragma once

#include "Action.h"

namespace ai
{
    class TellMasterAction : public Action {
    public:
        TellMasterAction(AiManagerRegistry* const ai, const char* text) : Action(ai, "tell master"), text(text) {}

        virtual bool Execute(Event event)
        {
            ai->GetAi()->TellMaster(text);
            return true;
        }

    private:
        string text;
    };

}