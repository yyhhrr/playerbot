#pragma once

#include "../Action.h"
#include "QuestAction.h"

namespace ai
{
    class AcceptQuestAction : public QuestAction {
    public:
        AcceptQuestAction(PlayerbotAI* ai) : QuestAction(ai, "accept quest") {}
        virtual bool Execute(Event event);

    protected:
        virtual void ProcessQuest(Quest const* quest, WorldObject* questGiver);
    };

    class AcceptQuestShareAction : public Action {
    public:
        AcceptQuestShareAction(PlayerbotAI* ai) : Action(ai, "accept quest share") {}
        virtual bool Execute(Event event);
    };
}