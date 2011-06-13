#pragma once

namespace ai
{
	class TaxiAction : public Action {
	public:
		TaxiAction(AiManagerRegistry* const ai) : Action(ai, "taxi") {}

    public:
        virtual bool Execute(Event event);
    };

}