#pragma once

#include "Action.h"

namespace ai
{
    class PassLeadershipToMasterAction : public Action {
    public:
        PassLeadershipToMasterAction(AiManagerRegistry* const ai) : Action(ai, "pass leadership to master") {}

        virtual bool Execute(Event event)
        {
            Player*  bot = ai->GetAi()->GetBot();
            Player* master = ai->GetAi()->GetMaster();
            WorldPacket &p = event.getPacket();

            string name;
            p >> name;
            if (bot->GetGroup() && name == bot->GetName())
            {
                if (bot->GetGroup()->IsMember(master->GetGUID()))
                {
                    p.resize(8);
                    p << master->GetGUID();
                    bot->GetSession()->HandleGroupSetLeaderOpcode(p);
                    return true;
                }
            }

            return false;
        }
    };

}