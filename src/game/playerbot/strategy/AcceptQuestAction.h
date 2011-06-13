#pragma once

#include "Action.h"

namespace ai
{
    class AcceptQuestAction : public Action {
    public:
        AcceptQuestAction(AiManagerRegistry* const ai) : Action(ai, "accept quest") {}
        virtual bool Execute(Event event);
    };

    class AcceptQuestShareAction : public Action {
    public:
        AcceptQuestShareAction(AiManagerRegistry* const ai) : Action(ai, "accept quest share") {}
        virtual bool Execute(Event event);
    };
}