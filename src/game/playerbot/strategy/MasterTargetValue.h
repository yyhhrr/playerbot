#pragma once
#include "Value.h"

namespace ai
{
    class MasterTargetValue : public CalculatedValue<Unit*>
	{
	public:
        MasterTargetValue(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}

        virtual Unit* Calculate() { return ai->GetAi()->GetMaster(); }
    };
}
