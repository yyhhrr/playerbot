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

    class OutOfReactRangeAction : public TellMasterAction {
    public:
        OutOfReactRangeAction(PlayerbotAI* ai) : TellMasterAction(ai, "Wait for me!") {}

        virtual bool Execute(Event event)
        {
            ai->SetNextCheckDelay(8);
            return TellMasterAction::Execute(event);
        }
   };
}