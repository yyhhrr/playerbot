#pragma once
#include "Value.h"
#include "TargetValue.h"
#include "..\ai\AttackerMapProvider.h"

namespace ai
{
   
    class AttackersValue : public CalculatedValue<AttackerMap>
	{
	public:
        AttackersValue(AiManagerRegistry* const ai) : CalculatedValue<AttackerMap>(ai), attackerMapProvider(NULL) 
        {
        }
        virtual ~AttackersValue() 
        {
            if (attackerMapProvider) 
                delete attackerMapProvider;
        }

    public:
        AttackerMap Calculate();

    private:
        AttackerMapProvider* attackerMapProvider;

    };
}
