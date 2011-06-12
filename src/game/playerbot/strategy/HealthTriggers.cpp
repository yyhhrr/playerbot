#include "../../pchdef.h"
#include "../playerbot.h"
#include "HealthTriggers.h"

using namespace ai;

float HealthInRangeTrigger::GetValue()
{
    return AI_VALUE2(uint8, "health", GetTargetName());
}

bool PartyMemberDeadTrigger::IsActive()
{
	return GetTarget();
}
