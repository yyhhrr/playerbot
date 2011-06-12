#include "../../pchdef.h"
#include "../playerbot.h"
#include "GenericActions.h"

using namespace ai;

bool CastSpellAction::Execute(Event event) 
{
	return spellManager->CastSpell(spell, GetTarget()); 
}

bool CastSpellAction::isPossible() 
{
	return spellManager->CanCastSpell(spell, GetTarget());
}

bool CastSpellAction::isUseful() 
{
	Unit* target = GetTarget();
	return target && spellManager->IsSpellCastUseful(spell, target);
}


bool CastAuraSpellAction::isPossible() 
{
	return CastSpellAction::isPossible() && !spellManager->HasAura(spell, GetTarget());
}

bool CastAuraSpellAction::isUseful() 
{
	return CastSpellAction::isUseful() && !spellManager->HasAura(spell, GetTarget());
}

bool CastHealingSpellAction::isUseful() 
{
	Unit* target = GetTarget();
	return CastSpellAction::isUseful() && statsManager->GetHealthPercent(target) < (100 - estAmount);
}


Value<Unit*>* CurePartyMemberAction::GetTargetValue()
{
    return ai->GetAi()->GetAiObjectContext()->GetValue<Unit*>("party member to dispel", dispelType);
}

Value<Unit*>* BuffOnPartyAction::GetTargetValue()
{
    return ai->GetAi()->GetAiObjectContext()->GetValue<Unit*>("party member without aura", spell);
}
