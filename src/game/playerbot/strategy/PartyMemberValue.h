#pragma once
#include "Value.h"

namespace ai
{
    class FindPlayerPredicate
    {
    public:
        virtual bool Check(Unit*) = NULL;
    };

    class SpellEntryPredicate
    {
    public:
        virtual bool Check(SpellEntry const*) = NULL;
    };

    class PartyMemberValue : public CalculatedValue<Unit*>
	{
	public:
        PartyMemberValue(PlayerbotAI* ai) : CalculatedValue<Unit*>(ai) {}

    public:
        bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate &predicate);

    protected:
        Unit* FindPartyMember(FindPlayerPredicate &predicate);
        bool Check(Unit* player);
	};
}
