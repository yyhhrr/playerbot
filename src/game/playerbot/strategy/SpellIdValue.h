#pragma once
#include "Value.h"
#include "TargetValue.h"
#include "..\ai\AttackerMapProvider.h"

namespace ai
{
   
    class SpellIdValue : public CalculatedValue<uint32>, public Qualified
	{
	public:
        SpellIdValue(AiManagerRegistry* const ai) : CalculatedValue<uint32>(ai) {}
      
    public:
        virtual uint32 Calculate();

    };
}
