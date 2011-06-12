#pragma once
#include "Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class CurrentCcTargetValue : public TargetValue, public Qualified
	{
	public:
        CurrentCcTargetValue(AiManagerRegistry* const ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };
}
