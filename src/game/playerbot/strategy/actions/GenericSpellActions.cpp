#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericActions.h"

using namespace ai;

bool CastSpellAction::Execute(Event event) 
{
	return ai->CastSpell(spell, GetTarget()); 
}

bool CastSpellAction::isPossible() 
{
	return ai->CanCastSpell(spell, GetTarget());
}

bool CastSpellAction::isUseful() 
{
	return GetTarget() && AI_VALUE2(bool, "spell cast useful", spell);
}


bool CastAuraSpellAction::isPossible() 
{
	return CastSpellAction::isPossible() && !ai->HasAura(spell, GetTarget());
}

bool CastAuraSpellAction::isUseful() 
{
	return CastSpellAction::isUseful() && !ai->HasAura(spell, GetTarget());
}

bool CastHealingSpellAction::isUseful() 
{
	return CastSpellAction::isUseful() && AI_VALUE2(uint8, "health", GetTargetName()) < (100 - estAmount);
}

bool CastAoeHealSpellAction::isUseful()
{
	return CastSpellAction::isUseful() && AI_VALUE2(uint8, "aoe heal", "medium") > 0;
}


Value<Unit*>* CurePartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member to dispel", dispelType);
}

Value<Unit*>* BuffOnPartyAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member without aura", spell);
}
