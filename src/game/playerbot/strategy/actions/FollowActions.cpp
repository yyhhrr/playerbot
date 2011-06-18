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
	Follow(AI_VALUE(Unit*, "master target"));
    return true;
}

bool FollowMasterRandomAction::Execute(Event event)
{
    float range = rand() % 10 + 2;
    float angle = GetFollowAngle();
    float x = master->GetPositionX() + cos(angle) * range;
    float y = master->GetPositionY() + sin(angle) * range;
    float z = master->GetPositionZ();

    MoveTo(master->GetMapId(), x, y, z);
    return true;
}
