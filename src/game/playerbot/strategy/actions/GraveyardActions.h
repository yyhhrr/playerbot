#pragma once

#include "../Action.h"

namespace ai
{
	class RepopAtGraveyardAction : public Action {
	public:
	    RepopAtGraveyardAction(PlayerbotAI* ai) : Action(ai, "graveyard") {}

    public:
        virtual bool Execute(Event event);
    };
}
