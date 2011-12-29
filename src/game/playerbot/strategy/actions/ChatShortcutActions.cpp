#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ChatShortcutActions.h"

using namespace ai;

bool FollowChatShortcutAction::Execute(Event event)
{
    ai->ChangeStrategy("+follow master,-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-follow master,-passive", BOT_STATE_COMBAT);
    ai->TellMaster("Will follow you");
    return true;
}

bool StayChatShortcutAction::Execute(Event event)
{
    ai->ChangeStrategy("+stay,-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-follow master,-passive", BOT_STATE_COMBAT);
    ai->TellMaster("Will stay in place");
    return true;
}

bool FleeChatShortcutAction::Execute(Event event)
{
    ai->ChangeStrategy("+follow master,+passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+follow master,+passive", BOT_STATE_COMBAT);
    ai->TellMaster("Will flee with you");
    return true;
}

bool GoawayChatShortcutAction::Execute(Event event)
{
    ai->ChangeStrategy("+runaway", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+runaway", BOT_STATE_COMBAT);
    ai->TellMaster("Will run away from target or you");
    return true;
}

bool GrindChatShortcutAction::Execute(Event event)
{
    ai->ChangeStrategy("+grind,-passive", BOT_STATE_NON_COMBAT);
    ai->TellMaster("Will start grinding");
    return true;
}
