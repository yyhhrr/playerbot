#pragma once
#include "Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberToDispel : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberToDispel(AiManagerRegistry* const ai) : 
          PartyMemberValue(ai) {}
    
    protected:
        virtual Unit* Calculate();
	};
}
