#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinActions.h"

using namespace ai;

bool SealTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return AI_VALUE2(uint8, "mana", "self target") > 30 && 
		!ai->HasAura("seal of justice", target) &&
        !ai->HasAura("seal of command", target) &&
		!ai->HasAura("seal of righteousness", target) &&
		!ai->HasAura("seal of light", target) &&
		!ai->HasAura("seal of wisdom", target);
}

bool CrusaderAuraTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return AI_VALUE(bool, "mounted") && !ai->HasAura("crusader aura", target);
}