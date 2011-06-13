#pragma once
#include "Value.h"
#include "../ai/LootObjectStack.h"

namespace ai
{
    class HasAvailableLootValue : public CalculatedValue<bool>
	{
	public:
        HasAvailableLootValue(AiManagerRegistry* const ai) : CalculatedValue<bool>(ai) {}

    public:
        virtual bool Calculate()
        {
            return AI_VALUE(LootObjectStack*, "available loot")->CanLoot(BOT_SIGHT_DISTANCE);
        }
    };
}
