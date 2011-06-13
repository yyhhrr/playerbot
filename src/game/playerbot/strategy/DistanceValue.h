#pragma once
#include "Value.h"
#include "TargetValue.h"

namespace ai
{
    class DistanceValue : public CalculatedValue<float>, public Qualified
	{
	public:
        DistanceValue(AiManagerRegistry* const ai) : CalculatedValue<float>(ai) {}

    public:
        float Calculate()
        {
            Unit* target = AI_VALUE(Unit*, qualifier.c_str());
            if (!target)
                return 0.0f;

            return ai->GetAi()->GetBot()->GetDistance(target);
        }
    };
}
