#pragma once
#include "Value.h"
#include "../ai/AiManagerRegistryAware.h"

namespace ai
{
    class NearestGameObjects : public CalculatedValue<list<GameObject*>>
	{
	public:
        NearestGameObjects(AiManagerRegistry* const ai, float range = BOT_SIGHT_DISTANCE) : 
            CalculatedValue<list<GameObject*>>(ai, list<GameObject*>()), range(range) {}
    
    protected:
        virtual list<GameObject*> Calculate();

    private:
        float range;
	};
}
