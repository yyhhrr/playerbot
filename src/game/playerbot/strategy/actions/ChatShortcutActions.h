#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class FollowChatShortcutAction : public Action {
    public:
        FollowChatShortcutAction(PlayerbotAI* ai) : Action(ai, "follow chat shortcut") {}
        virtual bool Execute(Event event);
    };

}
