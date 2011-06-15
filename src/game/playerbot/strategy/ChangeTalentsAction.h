#pragma once

#include "Action.h"

namespace ai
{
	class ChangeTalentsAction : public Action {
	public:
		ChangeTalentsAction(AiManagerRegistry* const ai) : Action(ai, "talents") {}

    public:
        virtual bool Execute(Event event);

    };

}