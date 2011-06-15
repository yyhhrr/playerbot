#include "../../pchdef.h"
#include "../playerbot.h"
#include "PartyMemberWithoutAuraValue.h"

using namespace ai;

class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public AiManagerRegistryAware
{
public:
    PlayerWithoutAuraPredicate(AiManagerRegistry* const ai, string aura) : 
        AiManagerRegistryAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        return unit->isAlive() && !ai->GetAi()->HasAura(aura.c_str(), unit);
    }

private:
    string aura;
};

Unit* PartyMemberWithoutAuraValue::Calculate()
{
    return FindPartyMember(PlayerWithoutAuraPredicate(ai, qualifier)); 
}
