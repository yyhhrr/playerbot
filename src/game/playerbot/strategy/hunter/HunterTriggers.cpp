#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "../triggers/GenericTriggers.h"
#include "../actions/GenericActions.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

bool HunterNoStingsActiveTrigger::IsActive()
{
	Unit* target = AI_VALUE(Unit*, "current target");
    return target && AI_VALUE2(uint8, "health", "current target") > 40 &&
        !ai->HasAura("serpent sting", target) && 
        !ai->HasAura("scorpid sting", target) &&
        !ai->HasAura("viper sting", target);
}

bool HuntersPetDeadTrigger::IsActive()
{
    Unit* pet = AI_VALUE(Unit*, "pet target");
    return pet && AI_VALUE2(bool, "dead", "pet target") && !AI_VALUE(bool, "mounted");
}


bool HuntersPetLowHealthTrigger::IsActive()
{
    Unit* pet = AI_VALUE(Unit*, "pet target");
    return pet && AI_VALUE2(uint8, "health", "pet target") < LOW_HEALTH_PERCENT && 
        !AI_VALUE2(bool, "dead", "pet target") && !AI_VALUE(bool, "mounted");
}
