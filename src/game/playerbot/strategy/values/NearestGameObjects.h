#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class NearestGameObjects : public CalculatedValue<list<GameObject*>>
	{
	public:
        NearestGameObjects(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
            CalculatedValue<list<GameObject*>>(ai), range(range) {}

    protected:
        virtual list<GameObject*> Calculate();

    private:
        float range;
	};
}
