#include "../../pchdef.h"
#include "../playerbot.h"
#include "MovementActions.h"

using namespace ai;

void FollowLineAction::Execute()
{
	ai->GetMoveManager()->Follow(ai->GetTargetManager()->GetLineTarget(), 2.0f, 0.0f);
}

void FollowMasterAction::Execute()
{
	ai->GetMoveManager()->Follow(ai->GetTargetManager()->GetMaster());
}

void StayAction::Execute()
{
    ai->GetMoveManager()->Stay();
}

void StayCircleAction::Execute()
{
	ai->GetMoveManager()->StayCircle(5.0f);
}

void GoAwayAction::Execute()
{
	ai->GetMoveManager()->Flee(ai->GetTargetManager()->GetMaster()); 
}
