#pragma once
#include "Value.h"

namespace ai
{
   
    class LastSpellIdValue : public ManualSetValue<uint32>
	{
	public:
        LastSpellIdValue(AiManagerRegistry* const ai) : ManualSetValue<uint32>(ai, 0) {}

    };
}
