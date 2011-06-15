#pragma once
#include "Value.h"
#include "TargetValue.h"
#include "..\ai\AttackerMapProvider.h"

namespace ai
{
   
    class ItemForSpellValue : public CalculatedValue<Item*>, public Qualified
	{
	public:
        ItemForSpellValue(AiManagerRegistry* const ai) : CalculatedValue<Item*>(ai) {}
      
    public:
        virtual Item* Calculate();

    };
}
