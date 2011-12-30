#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "UseMeetingStoneAction.h"

bool UseMeetingStoneAction::Execute(Event event)
{
    WorldPacket p(event.getPacket());
    p.rpos(0);
    ObjectGuid guid;
    p >> guid;

    if (master->GetSelectionGuid() && master->GetSelectionGuid() != bot->GetObjectGuid())
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
