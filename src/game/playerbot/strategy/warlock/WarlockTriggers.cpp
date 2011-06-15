#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockActions.h"

using namespace ai;

bool DemonArmorTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return AI_VALUE2(uint8, "mana", "self target") > 30 && 
		!ai->HasAura("demon skin", target) &&
		!ai->HasAura("demon armor", target);
}

bool SpellstoneTrigger::IsActive() 
{
    return BuffTrigger::IsActive() && AI_VALUE2(uint8, "item count", getName()) > 0;
}