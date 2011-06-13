#pragma once

#include "Action.h"

namespace ai
{
    class QueryQuestAction : public Action {
    public:
        QueryQuestAction(AiManagerRegistry* const ai) : Action(ai, "query quest") {}
        virtual bool Execute(Event event);
    };
}