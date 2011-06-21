#pragma once

#include "../Action.h"
#include "../../../QuestDef.h"

namespace ai
{
    class QuestAction : public Action {
    public:
        QuestAction(PlayerbotAI* ai, string name) : Action(ai, name) {}

    public:
        virtual bool Execute(Event event);

    protected:
        virtual void ProcessQuest(Quest const* quest, WorldObject* questGiver) = NULL;

    protected:
        bool AcceptQuest(Quest const* quest, uint64 questGiver);
        bool ProcessQuests(ObjectGuid questGiver);
        bool ProcessQuests(WorldObject* questGiver);
    };
}