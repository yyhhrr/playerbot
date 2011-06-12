#pragma once
#include "Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberToResurrect : public PartyMemberValue
	{
	public:
        PartyMemberToResurrect(AiManagerRegistry* const ai) : 
          PartyMemberValue(ai) {}
    
    protected:
        virtual Unit* Calculate();
	};
}
