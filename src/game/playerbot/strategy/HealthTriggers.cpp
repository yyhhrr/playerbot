#include "../../pchdef.h"
#include "../playerbot.h"
#include "HealthTriggers.h"

using namespace ai;

float HealthInRangeTrigger::GetValue()
{
	Unit* target = GetTarget();
	return target ? statsManager->GetHealthPercent(target) : 100.0f;
}

bool PartyMemberDeadTrigger::IsActive()
{
	return GetTarget();
}
