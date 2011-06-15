#pragma once

#include "Action.h"

namespace ai
{
    class UseMeetingStoneAction : public Action {
    public:
        UseMeetingStoneAction(PlayerbotAI* ai) : Action(ai, "use meeting stone") {}

        virtual bool Execute(Event event)
        {
            Player*  bot = ai->GetBot();

            WorldPacket p(event.getPacket());
            p.rpos(0);
            uint64 guid;
            p >> guid;

            Player* master = bot->GetPlayerbotAI()->GetMaster();
            if (master->GetSelectionGuid().GetRawValue() != bot->GetGUID())
                return false;

            GameObject* gameObject = master->GetMap()->GetGameObject(guid);
            if (!gameObject)
                return false;

            const GameObjectInfo* goInfo = gameObject->GetGOInfo();
            if (!goInfo || goInfo->type != GAMEOBJECT_TYPE_SUMMONING_RITUAL)
                return false;

            PlayerbotChatHandler ch(master);
            if (!ch.teleport(*bot))
            {
                ai->TellMaster("You cannot summon me");
                return false;
            }

            return true;
        }
    };

}