#pragma once
#include "Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class CcTargetValue : public TargetValue, public Qualified
	{
	public:
        CcTargetValue(AiManagerRegistry* const ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };
}
