#pragma once
#include "../Value.h"

namespace ai
{

    class LeastHpTargetValue : public CalculatedValue<Unit*>
	{
	public:
        LeastHpTargetValue(PlayerbotAI* ai) : CalculatedValue<Unit*>(ai) {}

    public:
        Unit* Calculate();
    };
}
