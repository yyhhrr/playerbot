#pragma once
#include "Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberWithoutAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberWithoutAuraValue(AiManagerRegistry* const ai, float range = BOT_SIGHT_DISTANCE) : 
          PartyMemberValue(ai) {}
    
    protected:
        virtual Unit* Calculate();
	};
}
