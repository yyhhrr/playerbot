#pragma once

#include "Action.h"

namespace ai
{
    class EmoteAction : public Action
    {
    public:
        EmoteAction(AiManagerRegistry* const ai, uint32 type) : Action(ai, "emote"), type(type) {}

        virtual bool Execute(Event event) 
        {
            ai->GetAi()->GetBot()->HandleEmoteCommand(type ? type : rand() % 450);
            return true;
        }

    private:
        uint32 type;
    };
}