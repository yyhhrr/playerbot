#pragma once
#include "Value.h"
#include "../ai/LootObjectStack.h"

namespace ai
{
   
    class AvailableLootValue : public ManualSetValue<LootObjectStack*>
	{
	public:
        AvailableLootValue(AiManagerRegistry* const ai) : ManualSetValue<LootObjectStack*>(ai, NULL) 
        {
            value = new LootObjectStack(ai->GetAi()->GetBot());
        }

        virtual ~AvailableLootValue()
        {
            if (value) 
                delete value;
        }
    };
}
