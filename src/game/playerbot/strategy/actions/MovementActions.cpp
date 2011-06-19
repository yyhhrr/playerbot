#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "../values/LastMovementValue.h"
#include "MovementActions.h"
#include "../../../MotionMaster.h"
#include "../../../MovementGenerator.h"
#include "../../AttackerMapProvider.h"
#include "../../FleeManager.h"
#include "../../LootObjectStack.h"

using namespace ai;

void MovementAction::MoveNear(uint32 mapId, float x, float y, float z, float distance)
{
    float angle = GetFollowAngle();
    MoveTo(mapId, x + cos(angle) * distance, y + sin(angle) * distance, z);
}

void MovementAction::MoveNear(WorldObject* target, float distance)
{
    if (!target)
        return;

    float angle = GetFollowAngle();
    MoveTo(target->GetMapId(), 
        target->GetPositionX() + cos(angle) * distance, 
        target->GetPositionY()+ sin(angle) * distance, 
        target->GetPositionZ());
}

void MovementAction::MoveTo(uint32 mapId, float x, float y, float z)
{
    if (!IsMovingAllowed(mapId, x, y, z))
        return;

    bot->UpdateGroundPositionZ(x, y, z);

    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    mm.MovePoint(mapId, x, y, z);
    WaitForReach(bot->GetDistance(x, y, z));

    AI_VALUE(LastMovement&, "last movement").Set(x, y, z, bot->GetOrientation());
}

void MovementAction::MoveTo(WorldObject* target)
{
    MoveTo(target->GetMapId(), target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
}

void MovementAction::MoveTo(Unit* target, float distance)
{
    if (!IsMovingAllowed(target))
        return;

    if (distance < SPELL_DISTANCE) 
    {
        Follow(target, distance);
        return;
    }

    float bx = bot->GetPositionX();
    float by = bot->GetPositionY();
    float bz = bot->GetPositionZ();

    float tx = target->GetPositionX();
    float ty = target->GetPositionY();
    float tz = target->GetPositionZ();

    float distanceToTarget = bot->GetDistance(target);

    float angle = bot->GetAngle(target);

    float destinationDistance = distanceToTarget - distance;
    float dx = cos(angle) * destinationDistance + bx;
    float dy = sin(angle) * destinationDistance + by;

    bot->UpdateGroundPositionZ(dx, dy, tz);
    MoveTo(target->GetMapId(), dx, dy, tz);
}
    
float MovementAction::GetFollowAngle()
{
    Group* group = bot->GetGroup();
    if (!group)
        return 0.0f;

    GroupReference *gref = group->GetFirstMember();
    int index = 1;
    while( gref )
    {
        if( gref->getSource() == bot)
            return 2 * M_PI / (group->GetMembersCount() -1) * index;

        gref = gref->next();
        index++;
    }
    return 0;
}

bool MovementAction::IsMovingAllowed(Unit* target) 
{
    if (!target)
        return false;

    if (bot->GetMapId() != target->GetMapId())
        return false;

    if (bot->GetDistance(target) > BOT_REACT_DISTANCE)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "I am too far away");
        return false;
    }

    return IsMovingAllowed();
}

bool MovementAction::IsMovingAllowed(uint32 mapId, float x, float y, float z)
{
    if (bot->GetMapId() != mapId || bot->GetDistance(x, y, z) > BOT_REACT_DISTANCE || !bot->IsWithinLOS(x, y, z))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Cannot move: not allowed");
        return false;
    }

    return IsMovingAllowed();
}

bool MovementAction::IsMovingAllowed() 
{
    if (bot->isFrozen() || bot->IsPolymorphed() || !bot->CanFreeMove() || bot->isDead())
        return false;

    MotionMaster &mm = *bot->GetMotionMaster();
    return mm->GetMovementGeneratorType() != FLIGHT_MOTION_TYPE;
}

void MovementAction::Follow(Unit* target, float distance)
{
    Follow(target, distance, GetFollowAngle());
}

void MovementAction::Follow(Unit* target, float distance, float angle)
{
    if (!IsMovingAllowed(target))
        return;

    if (target->IsFriendlyTo(bot) && bot->IsMounted())
        distance += angle;

    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    mm.MoveFollow(target, distance, angle);

    float distanceToRun = abs(bot->GetDistance(target) - distance);
    WaitForReach(distanceToRun);

    AI_VALUE(LastMovement&, "last movement").Set(target);
}

void MovementAction::WaitForReach(float distance)
{
    float delay = ceil(distance / bot->GetSpeed(MOVE_RUN)) + 1;
    
    if (delay < GLOBAL_COOLDOWN)
        delay = GLOBAL_COOLDOWN;
    
    if (delay > 8)
        delay = 8;

    bot->GetPlayerbotAI()->SetNextCheckDelay((uint32)delay);
}

bool MovementAction::Flee(Unit *target)
{
    if (!target)
        return false;

    if (!IsMovingAllowed())
        return true;

    AttackerMap attackers = context->GetValue<AttackerMap>("attackers")->Get();
    FleeManager manager(bot, &attackers, SPELL_DISTANCE, GetFollowAngle());

    float rx, ry, rz;
    if (!manager.CalculateDestination(&rx, &ry, &rz)) 
        return false;

    MoveTo(0, rx, ry, rz);
    return true;
}

bool FleeAction::Execute(Event event)
{
    return Flee(AI_VALUE(Unit*, "current target")); 
}

bool GoAwayAction::Execute(Event event)
{
    return Flee(AI_VALUE(Unit*, "master target")); 
}

bool MoveRandomAction::Execute(Event event)
{
    WorldObject* target = NULL;

    if (rand() % 2)
    {
        list<Unit*> npcs = AI_VALUE(list<Unit*>, "nearest npcs");
        if (!npcs.empty())
        {
            size_t pos = rand() % npcs.size();
            for (list<Unit*>::iterator i = npcs.begin(); i != npcs.end() && pos; i++)
            {
                target = *i;
                pos--;
                if (!pos)
                {
                    ostringstream out; out << "I will check " << (*i)->GetName();
                    ai->TellMaster(out);
                }
            }
        }
    }

    if (!target)
    {
        list<GameObject*> gos = AI_VALUE(list<GameObject*>, "nearest game objects");
        if (!gos.empty())
        {
            size_t pos = rand() % gos.size();
            for (list<GameObject*>::iterator i = gos.begin(); i != gos.end() && pos; i++)
            {
                target = *i;
                pos--;
                if (!pos)
                {
                    AI_VALUE(LootObjectStack*, "available loot")->Add(target->GetObjectGuid());
                    ostringstream out; out << "I will check " << chat->formatGameobject(*i);
                    ai->TellMaster(out);
                }
            }
        }
    }

    if (!target)
        return false;
    
    float distance = (rand() % 15) / 10.0f;
    MoveNear(target);
    return true;
}
