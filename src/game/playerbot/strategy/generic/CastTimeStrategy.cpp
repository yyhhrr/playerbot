#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "CastTimeStrategy.h"
#include "../CastTimeMultiplier.h"

using namespace ai;

void CastTimeStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new CastTimeMultiplier(ai));
}
