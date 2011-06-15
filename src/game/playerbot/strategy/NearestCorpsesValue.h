#pragma once
#include "Value.h"
#include "NearestUnitsValue.h"

namespace ai
{
    class NearestCorpsesValue : public NearestUnitsValue
	{
	public:
        NearestCorpsesValue(PlayerbotAI* ai, float range = BOT_SIGHT_DISTANCE) : 
          NearestUnitsValue(ai) {}
    
    protected:
        virtual list<Unit*> Calculate();
    
	};
}
