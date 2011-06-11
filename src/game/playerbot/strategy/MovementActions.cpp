#include "../../pchdef.h"
#include "../playerbot.h"
#include "MovementActions.h"

using namespace ai;

bool FollowLineAction::Execute(Event event)
{
	ai->GetMoveManager()->Follow(ai->GetTargetManager()->GetLineTarget(), 2.0f, 0.0f);
    return true;
}

bool FollowMasterAction::Execute(Event event)
{
	ai->GetMoveManager()->Follow(ai->GetTargetManager()->GetMaster());
    return true;
}

bool StayAction::Execute(Event event)
{
    ai->GetMoveManager()->Stay();
    return true;
}

bool StayCircleAction::Execute(Event event)
{
	ai->GetMoveManager()->StayCircle(2.0f);
    return true;
}

bool StayLineAction::Execute(Event event)
{
	ai->GetMoveManager()->StayLine(2.0f);
    return true;
}

bool StayCombatAction::Execute(Event event)
{
	ai->GetMoveManager()->StayCombat(2.0f);
    return true;
}

bool GoAwayAction::Execute(Event event)
{
	ai->GetMoveManager()->Flee(ai->GetTargetManager()->GetMaster()); 
    return true;
}
