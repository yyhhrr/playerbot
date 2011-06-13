#pragma once
#include "Value.h"

namespace ai
{
    class LootStrategyValue : public ManualSetValue<LootStrategy>
	{
	public:
        LootStrategyValue(AiManagerRegistry* const ai) : ManualSetValue<LootStrategy>(ai, LOOTSTRATEGY_QUEST) {}
    };
}
