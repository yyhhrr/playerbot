#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PossibleTargetsValue.h"

#include "../../../GridNotifiers.h"
#include "../../../GridNotifiersImpl.h"
#include "../../../CellImpl.h"

using namespace ai;
using namespace MaNGOS;


list<Unit*> PossibleTargetsValue::Calculate()
{
    

    list<Unit *> targets;

    MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, bot, range);
    MaNGOS::UnitListSearcher<MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);

    RemoveNotInLOS(targets);
    return targets;
}