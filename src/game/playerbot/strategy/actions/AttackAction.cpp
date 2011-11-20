#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AttackAction.h"
#include "../../../MovementGenerator.h"
#include "../../../CreatureAI.h"
#include "../../LootObjectStack.h"

using namespace ai;

bool AttackAction::Execute(Event event)
{
    Unit* target = GetTarget();

    if (!target)
        return false;

    return Attack(target);
}

bool AttackMyTargetAction::Execute(Event event)
{

    ObjectGuid guid = master->GetSelectionGuid();
    if (!guid)
        return false;

    return Attack(ai->GetCreature(guid));
}

bool AttackAction::Attack(Unit* target)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm->GetMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return false;

    if (!target)
        return false;

    if (bot->IsFriendlyTo(target))
    {
        ai->TellMaster("Target is friendly");
        return false;
    }
    if (!bot->IsWithinLOSInMap(target))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Target is not in my sight");
        return false;
    }

    if (bot->getStandState() != UNIT_STAND_STATE_STAND)
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    if (bot->IsMounted())
    {
        WorldPacket emptyPacket;
        bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
    }

    ObjectGuid guid = target->GetObjectGuid();
    bot->SetSelectionGuid(target->GetObjectGuid());

    if (!bot->isInFront(target, ATTACK_DISTANCE))
        bot->SetFacingTo(bot->GetAngle(target));

    context->GetValue<Unit*>("current target")->Set(target);
    context->GetValue<LootObjectStack*>("available loot")->Get()->Add(guid);

    bool alreadyAttacking = (bot->getVictim() == target && bot->hasUnitState(UNIT_STAT_MELEE_ATTACKING));
    if (alreadyAttacking)
        return false;

    bot->Attack(target, true);

    Pet* pet = bot->GetPet();
    if (pet)
    {
        CreatureAI* creatureAI = ((Creature*)pet)->AI();
        if (creatureAI)
            creatureAI->AttackStart(target);
    }

    return true;
}
