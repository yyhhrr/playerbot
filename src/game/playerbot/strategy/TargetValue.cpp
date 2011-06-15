#include "../../pchdef.h"
#include "../playerbot.h"
#include "TargetValue.h"

using namespace ai;

Unit* TargetValue::FindTarget(FindTargetStrategy* strategy)
{
    Player* bot = ai->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
    {
        strategy->CheckAttackers(bot, bot);
        return strategy->GetResult();
    }

    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* member = gref->getSource();
        if (!member || !member->isAlive() || !member->IsWithinLOSInMap(member))
            continue;

        strategy->CheckAttackers(bot, member);
    }

    return strategy->GetResult();
}


void FindTargetStrategy::CheckAttackers(Player* bot, Player* player)
{
    for (HostileReference* ref = player->getHostileRefManager().getFirst(); ref; ref = ref->next())
    {
        ThreatManager* threatManager = ref->getSource();
        Unit *attacker = threatManager->getOwner();
        if (attacker && alreadyChecked.find(attacker) == alreadyChecked.end() &&
            !attacker->isDead() && 
            !attacker->IsPolymorphed() && 
            !attacker->isFrozen() && 
            !attacker->IsFriendlyTo(bot) && 
            bot->IsWithinLOSInMap(attacker))
        {
            CheckAttacker(bot, player, threatManager);
            alreadyChecked.insert(attacker);
            if (alreadyChecked.size() > 5)
                break;
        }
    }
}

void FindTargetStrategy::GetPlayerCount(Player* bot, Unit* creature, int* tankCount, int* dpsCount)
{
    if (tankCountCache.find(creature) != tankCountCache.end())
    {
        *tankCount = tankCountCache[creature];
        *dpsCount = dpsCountCache[creature];
        return;
    }

    *tankCount = 0;
    *dpsCount = 0;

    for (set<Unit*>::const_iterator i = creature->getAttackers().begin(); i != creature->getAttackers().end(); i++)
    {
        Unit* attacker = *i;
        if (!attacker || !attacker->isAlive() || attacker == bot)
            continue;

        Player* player = dynamic_cast<Player*>(attacker);
        if (!player)
            continue;

        if (ai->IsTank(player))
            (*tankCount)++;
        else
            (*dpsCount)++;
    }

    tankCountCache[creature] = *tankCount;
    dpsCountCache[creature] = *dpsCount;
}
