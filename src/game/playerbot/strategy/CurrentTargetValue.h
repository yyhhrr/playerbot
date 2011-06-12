#pragma once
#include "Value.h"

namespace ai
{
    class CurrentTargetValue : public ManualSetValue<Unit*>
	{
	public:
        CurrentTargetValue(AiManagerRegistry* const ai) : ManualSetValue<Unit*>(ai, NULL) {}

        virtual Unit* Get();
        virtual void Set(Unit* unit);
	
    private:
        ObjectGuid selection;
    };
}
