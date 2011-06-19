#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
    class DistanceValue : public CalculatedValue<float>, public Qualified
	{
	public:
        DistanceValue(PlayerbotAI* ai) : CalculatedValue<float>(ai) {}

    public:
        float Calculate()
        {
            Unit* target = AI_VALUE(Unit*, qualifier);
            if (!target)
                return 0.0f;

            return ai->GetBot()->GetDistance(target);
        }
    };
}
