#pragma once
#include "Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class DpsTargetValue : public TargetValue
	{
	public:
        DpsTargetValue(AiManagerRegistry* const ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };
}
