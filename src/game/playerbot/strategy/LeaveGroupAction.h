#pragma once

#include "Action.h"

namespace ai
{
    class LeaveGroupAction : public Action {
    public:
        LeaveGroupAction(AiManagerRegistry* const ai) : Action(ai, "leave") {}
        
        virtual bool ExecuteResult()
        {
            Group* group = GetBot()->GetGroup();
            if (!group) 
                return false;

            group->RemoveMember(GetBot()->GetObjectGuid(), 0);
            return true;
        }
    };

}