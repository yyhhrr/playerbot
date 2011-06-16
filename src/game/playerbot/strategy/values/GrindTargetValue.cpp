#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GrindTargetValue.h"

using namespace ai;

Unit* GrindTargetValue::Calculate()
{
    
    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    Unit* target = NULL;
    uint32 assistCount = 0;
    while (!target && assistCount < group->GetMembersCount())
    {
        target = FindTargetForGrinding(assistCount++);
    }

    return target;
}


Unit* GrindTargetValue::FindTargetForGrinding(int assistCount) 
{
    
    
    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    
    list<Unit*> targets = *context->GetValue<list<Unit*>>("possible targets");

    if(targets.empty())
        return NULL;

    float distance = 0;
    Unit* result = NULL;
    for(list<Unit *>::iterator tIter = targets.begin(); tIter != targets.end(); tIter++)
    {
        Unit* unit = *tIter;

        if (abs(bot->GetPositionZ() - unit->GetPositionZ()) > SPELL_DISTANCE)
            continue;

        if (GetTargetingPlayerCount(unit) > assistCount)
            continue;

        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *member = sObjectMgr.GetPlayer(itr->guid);
            if( !member || !member->isAlive())
                continue;

            if (master->GetDistance(unit) >= BOT_GRIND_DISTANCE)
                continue;

            float d = member->GetDistance(unit);
            if (!result || d < distance)
            {
                distance = d;
                result = unit;
            }
        }
    }

    return result;
}


int GrindTargetValue::GetTargetingPlayerCount( Unit* unit ) 
{
    
    Group* group = bot->GetGroup();
    if (!group)
        return 0;

    int count = 0;
    Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
    {
        Player *member = sObjectMgr.GetPlayer(itr->guid);
        if( !member || !member->isAlive() || member == bot)
            continue;

        PlayerbotAI* ai = member->GetPlayerbotAI();
        if ((ai && context->GetValue<Unit*>("current target")->Get() == unit) ||
            (!ai && member->GetSelectionGuid() == unit->GetObjectGuid()))
            count++;
    }

    return count;
}

