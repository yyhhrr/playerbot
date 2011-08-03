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
        name == "reset ai" ||
        name == "stay" ||
        name.find("chat shortcut") != string::npos)
        return 1.0f;

    return 0;
}
