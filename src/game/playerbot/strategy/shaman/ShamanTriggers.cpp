#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanTriggers.h"
#include "ShamanActions.h"

using namespace ai;

bool ShamanWeaponTrigger::IsActive()
{
    return SpellTrigger::IsActive()
            && !ai->HasAnyAuraOf(GetTarget(), "frostbrand weapon", "rockbiter weapon", "flametongue weapon",
                    "earthliving weapon", "windfury weapon", NULL);
}
