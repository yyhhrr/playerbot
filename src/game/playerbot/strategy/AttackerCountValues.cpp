#include "../../pchdef.h"
#include "../playerbot.h"
#include "../ai/AttackerMapProvider.h"
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

    AttackerMap attackers = ai->GetAi()->GetAiObjectContext()->GetValue<AttackerMap>("attackers")->Get();
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
    Player* bot = ai->GetAi()->GetBot();
    Player* master = ai->GetAi()->GetMaster();

    float playerLevel = 0,
        attackerLevel = 0;

    Group* group = master->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *player = sObjectMgr.GetPlayer(itr->guid);
            if( !player || !player->isAlive())
                continue;

            playerLevel += player->getLevel();
        }
    }

    AttackerMap v = ai->GetAi()->GetAiObjectContext()->GetValue<AttackerMap>("attackers")->Get();

    for (AttackerMapIterator i = v.begin(); i!=v.end(); i++)
    {  
        Creature* creature = master->GetMap()->GetCreature(i->first);
        if (!creature || !creature->isAlive())
            continue;

        uint32 level = creature->getLevel();

        switch (creature->GetCreatureInfo()->rank) {
        case CREATURE_ELITE_RARE:
            level *= 2;
            break;
        case CREATURE_ELITE_ELITE:
            level *= 3;
            break;
        case CREATURE_ELITE_RAREELITE:
            level *= 3;
            break;
        case CREATURE_ELITE_WORLDBOSS:
            level *= 5;
            break;
        }
        attackerLevel += level;
    }

    return attackerLevel ? playerLevel * 100 / attackerLevel : 100;
}

