#pragma once
#include "../Value.h"

namespace ai
{
    class NearestUnitsValue : public CalculatedValue<list<Unit*>>
	{
	public:
        NearestUnitsValue(PlayerbotAI* ai, float range = BOT_SIGHT_DISTANCE) : 
            CalculatedValue<list<Unit*>>(ai), range(range) {}
    
    protected:
        void RemoveNotInLOS( list<Unit *> &targets ) 
        {
            

            for(list<Unit *>::iterator tIter = targets.begin(); tIter != targets.end();)
            {
                if(!bot->IsWithinLOSInMap(*tIter))
                {
                    list<Unit *>::iterator tIter2 = tIter;
                    ++tIter;
                    targets.erase(tIter2);
                }
                else
                    ++tIter;
            }
        }
    
    protected:
        float range;
	};
}
