#pragma once

#include "../Action.h"

namespace ai
{
    class RtiAction : public Action
    {
    public:
        RtiAction(PlayerbotAI* ai) : Action(ai, "rti")
        {}

        virtual bool Execute(Event event)
        {
            string text = event.getParam();
            if (text.empty() || text == "?")
            {
                ostringstream out; out << "RTI: " << AI_VALUE(string, "rti");
                ai->TellMaster(out);
                return true;
            }

            context->GetValue<string>("rti")->Set(text);
            return true;
        }
    };

}
