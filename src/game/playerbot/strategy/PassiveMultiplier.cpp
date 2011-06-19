#include "../../pchdef.h"
#include "../playerbot.h"
#include "PassiveMultiplier.h"

using namespace ai;

float PassiveMultiplier::GetValue(Action* action) {
    if (!action) 
		return 1.0f;

    string name = action->getName();

    if (name == "follow" ||
        name == "co" ||
        name == "nc" ||
        name == "stay")
        return 1.0f;

    return 0;
}