#pragma once

#include "Action.h"

namespace ai
{
    class AcceptInvitationAction : public Action {
    public:
        AcceptInvitationAction(AiManagerRegistry* const ai) : Action(ai, "accept invitation") {}

        virtual bool ExecuteResult()
        {
            Player*  bot = ai->GetAi()->GetBot();

            Group* grp = bot->GetGroupInvite();
            if (!grp)
                return false;

            Player* inviter = sObjectMgr.GetPlayer(grp->GetLeaderGuid());
            if (!inviter)
                return false;

            WorldPacket p;
            uint32 roles_mask = 0;
            p << roles_mask;
            bot->GetSession()->HandleGroupAcceptOpcode(p);

            return true;
        }
    };

}