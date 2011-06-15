#pragma once

#include "../Action.h"

namespace ai
{
    class TurnInQuestAction : public Action {
    public:
        TurnInQuestAction(PlayerbotAI* ai) : Action(ai, "turn in quest") {}
        virtual bool Execute(Event event);

    private:
        void TurnInQuests(WorldObject *questgiver);
    };

}