#pragma once
#include "Value.h"
#include "NearestUnitsValue.h"

namespace ai
{
    class PossibleTargetsValue : public NearestUnitsValue
	{
	public:
        PossibleTargetsValue(AiManagerRegistry* const ai, float range = BOT_SIGHT_DISTANCE) : 
          NearestUnitsValue(ai) {}
    
    protected:
        virtual list<Unit*> Calculate();
    
	};
}
