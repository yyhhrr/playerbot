#pragma once
#include "Value.h"
#include "../PlayerbotAIAware.h"

namespace ai
{
    class NearestGameObjects : public CalculatedValue<list<GameObject*>>
	{
	public:
        NearestGameObjects(PlayerbotAI* ai, float range = BOT_SIGHT_DISTANCE) : 
            CalculatedValue<list<GameObject*>>(ai), range(range) {}
    
    protected:
        virtual list<GameObject*> Calculate();

    private:
        float range;
	};
}
