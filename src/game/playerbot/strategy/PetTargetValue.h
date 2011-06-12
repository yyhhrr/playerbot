#pragma once
#include "Value.h"

namespace ai
{
    class PetTargetValue : public CalculatedValue<Unit*>
	{
	public:
        PetTargetValue(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}

        virtual Unit* Calculate() { return ai->GetAi()->GetBot()->GetPet(); }
    };
}
