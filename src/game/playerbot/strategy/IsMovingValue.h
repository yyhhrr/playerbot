#pragma once
#include "Value.h"

namespace ai
{
    class IsMovingValue : public CalculatedValue<bool>, public Qualified
	{
	public:
        IsMovingValue(PlayerbotAI* ai) : CalculatedValue<bool>(ai) {}

        virtual bool Calculate() 
        {
            Unit* target = AI_VALUE(Unit*, qualifier.c_str());

            if (!target)
                return false;

            switch (target->GetMotionMaster()->GetCurrentMovementGeneratorType())
            {
            case IDLE_MOTION_TYPE:
                return false;
            }
            return true;
        }
    };
}
