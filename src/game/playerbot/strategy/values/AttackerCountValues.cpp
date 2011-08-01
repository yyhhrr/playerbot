#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AttackerCountValues.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

uint8 MyAttackerCountValue::Calculate()
{
    return bot->getAttackers().size();
}

bool HasAggroValue::Calculate()
{

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


    int count = 0;
    float range = sPlayerbotAIConfig.sightDistance;

    list<Unit*> attackers = context->GetValue<list<Unit*>>("attackers")->Get();
    for (list<Unit*>::iterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* unit = *i;
        float distance = unit->GetDistance(bot);
        if (distance <= range)
            count++;
    }

    return count;
}

uint8 BalancePercentValue::Calculate()
{



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

    list<Unit*> v = context->GetValue<list<Unit*>>("attackers")->Get();

    for (list<Unit*>::iterator i = v.begin(); i!=v.end(); i++)
    {
        Creature* creature = ai->GetCreature((*i)->GetObjectGuid());
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

    if (!attackerLevel)
        return 100;

    float percent = playerLevel * 100 / attackerLevel;
    return percent <= 200 ? (uint8)percent : 200;
}

