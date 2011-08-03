#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ChatShortcutActions.h"

using namespace ai;

bool FollowChatShortcutAction::Execute(Event event)
{
    ai->ChangeStrategy("-stay,+follow master,-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-passive", BOT_STATE_COMBAT);
    ai->TellMaster("I am following you");
    return true;
}
