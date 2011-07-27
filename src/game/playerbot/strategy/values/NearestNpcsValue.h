#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class NearestNpcsValue : public NearestUnitsValue
	{
	public:
        NearestNpcsValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          NearestUnitsValue(ai) {}

    protected:
        virtual list<Unit*> Calculate();

	};
}
