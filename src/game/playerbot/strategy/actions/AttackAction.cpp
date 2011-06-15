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
    Player* master = ai->GetMaster();
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

    if (bot->IsFriendlyTo(target))
    {
        ai->TellMaster("Target is friendly");
        return false;
    }
    if (!bot->IsWithinLOSInMap(target))
    {
        ai->TellMaster("Target is not in my sight");
        return false;
    }

    if (bot->getStandState() != UNIT_STAND_STATE_STAND)
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    if (bot->IsMounted())
    {
        WorldPacket emptyPacket;
        bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
    }

    uint64 guid = target->GetGUID();
    bot->SetSelectionGuid(target->GetObjectGuid());
    bot->Attack(target, true);
    bot->SetInFront(target);

    Pet* pet = bot->GetPet();
    if (pet)
    {
        CreatureAI* creatureAI = ((Creature*)pet)->AI();
        if (creatureAI)
            creatureAI->AttackStart(target);
    }

    
    ai->GetAiObjectContext()->GetValue<Unit*>("current target")->Set(target);
    ai->GetAiObjectContext()->GetValue<LootObjectStack*>("available loot")->Get()->Add(guid);

    return true;
}
