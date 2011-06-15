#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "FollowActions.h"

using namespace ai;

bool FollowLineAction::Execute(Event event)
{
	Follow(AI_VALUE(Unit*, "line target"), 2.0f, 0.0f);
    return true;
}

bool FollowMasterAction::Execute(Event event)
{
	Follow(AI_VALUE(Unit*, "master"));
    return true;
}
