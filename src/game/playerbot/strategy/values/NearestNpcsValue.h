#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"

namespace ai
{
    class NearestNpcsValue : public NearestUnitsValue
	{
	public:
        NearestNpcsValue(PlayerbotAI* ai, float range = BOT_SIGHT_DISTANCE) : 
          NearestUnitsValue(ai) {}
    
    protected:
        virtual list<Unit*> Calculate();
    
	};
}
