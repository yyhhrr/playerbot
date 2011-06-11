#pragma once
#include "Value.h"
#include "../ai/AiManagerRegistryAware.h"

namespace ai
{
    class NearestGameObjects : public Value<list<GameObject*>>
	{
	public:
        NearestGameObjects(AiManagerRegistry* const ai, float range = BOT_SIGHT_DISTANCE) : 
            Value<list<GameObject*>>(ai), range(range) {}
    
    protected:
        virtual list<GameObject*> Calculate();

    private:
        float range;
	};
}
