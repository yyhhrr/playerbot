#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "LeastHpTargetValue.h"

using namespace ai;
using namespace std;

Unit* LeastHpTargetValue::Calculate()
{
    Unit* target = NULL;

    list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "attackers");
    for (list<ObjectGuid>::iterator i = targets.begin(); i != targets.end(); ++i)
    {
        Unit* unit = ai->GetUnit(*i);
        if (!unit)
            continue;

        if (!target || target->GetHealth() > unit->GetHealth())
            target = unit;
    }

    return target;
}
