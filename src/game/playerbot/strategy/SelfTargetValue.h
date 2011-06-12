#pragma once
#include "Value.h"

namespace ai
{
    class SelfTargetValue : public CalculatedValue<Unit*>
	{
	public:
        SelfTargetValue(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}

        virtual Unit* Calculate() { return ai->GetAi()->GetBot(); }
    };
}
