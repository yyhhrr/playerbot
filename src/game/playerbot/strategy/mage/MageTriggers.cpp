#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageTriggers.h"
#include "MageActions.h"

using namespace ai;

bool MageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return AI_VALUE2(uint8, "mana", "self target") > 30 && 
        !ai->GetAi()->HasAura("ice armor", target) &&
        !ai->GetAi()->HasAura("frost armor", target) &&
        !ai->GetAi()->HasAura("mage armor", target);
}