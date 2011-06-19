#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "NearestNpcsValue.h"

#include "../../../GridNotifiers.h"
#include "../../../GridNotifiersImpl.h"
#include "../../../CellImpl.h"

using namespace ai;
using namespace MaNGOS;


list<Unit*> NearestNpcsValue::Calculate()
{
    

    list<Unit *> targets;

    AnyFriendlyUnitInObjectRangeCheck u_check(bot, range);
    UnitListSearcher<AnyFriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);

    RemoveNotInLOS(targets);

    for(list<Unit *>::iterator tIter = targets.begin(); tIter != targets.end();)
    {
        if (dynamic_cast<Player*>(*tIter))
        {
            list<Unit *>::iterator tIter2 = tIter;
            ++tIter;
            targets.erase(tIter2);
        }
        else
            ++tIter;
    }

    return targets;
}