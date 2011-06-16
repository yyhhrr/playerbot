#pragma once

#include "../Action.h"

namespace ai
{
    class LeaveGroupAction : public Action {
    public:
        LeaveGroupAction(PlayerbotAI* ai) : Action(ai, "leave") {}
        
        virtual bool Execute(Event event)
        {
            Group* group = bot->GetGroup();
            if (!group) 
                return false;

            group->RemoveMember(bot->GetObjectGuid(), 0);
            return true;
        }
    };

}