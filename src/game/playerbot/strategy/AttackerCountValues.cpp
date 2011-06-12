#include "../../pchdef.h"
#include "../playerbot.h"
#include "AttackerCountValues.h"

using namespace ai;

uint8 MyAttackerCountValue::Calculate()
{
    Player* bot = ai->GetAi()->GetBot();
    return bot->getAttackers().size();
}

bool HasAggroValue::Calculate()
{
    Player* bot = ai->GetAi()->GetBot();
    Unit* target = GetTarget();
    if (!target)
        return true;

    HostileReference *ref = bot->getHostileRefManager().getFirst();
    if (!ref)
        return true; // simulate as target is not atacking anybody yet

    while( ref )
    {
        ThreatManager *threatManager = ref->getSource();
        Unit *attacker = threatManager->getOwner();
        Unit *victim = attacker->getVictim();
        if (victim == bot && target == attacker)
            return true;
        ref = ref->next();
    }
    return false;
}

uint8 AttackerCountValue::Calculate()
{
    Player* bot = ai->GetAi()->GetBot();

    int count = 0;
    float range = BOT_SIGHT_DISTANCE;

    AttackerMap attackers = ai->GetAi()->GetGroupStatsManager()->GetAttackers();
    for (AttackerMapIterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* unit = sObjectAccessor.GetUnit(*bot, i->first);
        if (!unit)
            continue;

        float distance = unit->GetDistance(bot);
        if (distance <= range)
            count++;
    }

    return count;
}

uint8 BalancePercentValue::Calculate()
{
    return ai->GetAi()->GetGroupStatsManager()->GetBalancePercent();
}

