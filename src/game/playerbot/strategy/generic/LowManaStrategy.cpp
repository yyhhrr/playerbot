#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "LowManaStrategy.h"
#include "../LowManaMultiplier.h"

using namespace ai;

void LowManaStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new LowManaMultiplier());
}
