#pragma once
#include "../Value.h"
#include "../LootObjectStack.h"

namespace ai
{
    class HasAvailableLootValue : public CalculatedValue<bool>
	{
	public:
        HasAvailableLootValue(PlayerbotAI* ai) : CalculatedValue<bool>(ai) {}

    public:
        virtual bool Calculate()
        {
            return !AI_VALUE(bool, "can loot") &&
                    AI_VALUE(LootObjectStack*, "available loot")->CanLoot(BOT_SIGHT_DISTANCE) &&
                    !bot->IsMounted();
        }
    };
}
