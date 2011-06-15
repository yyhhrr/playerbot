#pragma once

#include "Action.h"

namespace ai
{
    class QueryQuestItemAction : public Action {
    public:
        QueryQuestItemAction(PlayerbotAI* ai) : Action(ai, "query quest item") {}
        virtual bool Execute(Event event);

    private:
        void QueryQuestItem(uint32 itemId, const Quest *questTemplate, QuestStatusData *questStatus);
        void QueryQuestItem(uint32 itemId);

    };
}