#pragma once

#include "Action.h"

namespace ai
{
    class TellReputationAction : public Action {
    public:
        TellReputationAction(AiManagerRegistry* const ai) : Action(ai, "reputation") {}
        virtual bool Execute(Event event);

    private:

    };

}