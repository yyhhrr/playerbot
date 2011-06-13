#pragma once

namespace ai
{
	class RememberTaxiAction : public Action {
	public:
		RememberTaxiAction(AiManagerRegistry* const ai) : Action(ai, "remember taxi") {}

    public:
        virtual bool Execute(Event event);
    };

}