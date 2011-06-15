#pragma once
#include "Value.h"
#include "../LootObjectStack.h"

namespace ai
{
   
    class AvailableLootValue : public ManualSetValue<LootObjectStack*>
	{
	public:
        AvailableLootValue(PlayerbotAI* ai) : ManualSetValue<LootObjectStack*>(ai, NULL) 
        {
            value = new LootObjectStack(ai->GetBot());
        }

        virtual ~AvailableLootValue()
        {
            if (value) 
                delete value;
        }
    };
}
