#pragma once
#include "Value.h"
#include "TargetValue.h"
#include "..\ai\AttackerMapProvider.h"

namespace ai
{
   
    class SpellCastUsefulValue : public CalculatedValue<bool>, public Qualified
	{
	public:
        SpellCastUsefulValue(AiManagerRegistry* const ai) : CalculatedValue<bool>(ai) {}
      
    public:
        virtual bool Calculate();

    };
}
