#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterActions.h"
#include "HunterActionFactory.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterBuffStrategies.h"

using namespace ai;

Strategy* HunterActionFactory::createStrategy(const char* name)
{
    if (!strcmp("dps", name))
        return new DpsHunterStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericHunterNonCombatStrategy(ai);

    if (!strcmp("bspeed", name))
        return new HunterBuffSpeedNonCombatStrategy(ai);

	if (!strcmp("bdps", name))
		return new HunterBuffDpsStrategy(ai);

	if (!strcmp("rnature", name))
		return new HunterNatureResistanceStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;
    return new GenericHunterStrategy(ai);
}
