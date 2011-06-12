#pragma once
#include "Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class TankTargetValue : public TargetValue
	{
	public:
        TankTargetValue(AiManagerRegistry* const ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };
}
