#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AreaTriggerAction.h"


using namespace ai;

bool ReachAreaTriggerAction::Execute(Event event)
{
    Player*  bot = ai->GetBot();
    Player* master = bot->GetPlayerbotAI()->GetMaster();

    uint32 triggerId;
    WorldPacket p(event.getPacket());
    p.rpos(0);
    p >> triggerId;

    AreaTriggerEntry const* atEntry = sAreaTriggerStore.LookupEntry(triggerId);
    if(!atEntry)
        return false;

    AreaTrigger const* at = sObjectMgr.GetAreaTrigger(triggerId);
    if (!at)
    {
        WorldPacket p1(CMSG_AREATRIGGER);
        p1 << triggerId;
        p1.rpos(0);
        bot->GetSession()->HandleAreaTriggerOpcode(p1);
        
        return true;
    }

    if (bot->GetMapId() != atEntry->mapid || bot->GetDistance(atEntry->x, atEntry->y, atEntry->z) > BOT_SIGHT_DISTANCE)
    {
        ai->TellMaster("I will not follow you - too far away");
        return true;
    }

    ai->ChangeNonCombatStrategy("-follow,+stay");
    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    bot->TeleportTo(atEntry->mapid, atEntry->x, atEntry->y, atEntry->z, 0.0f, TELE_TO_NOT_LEAVE_TRANSPORT);
    bot->SendHeartBeat(false);
    ai->SetNextCheckDelay(3);
    ai->TellMaster("I will teleport in 3 seconds");
    
    ai->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get().lastAreaTrigger = triggerId;
    
    return true;
}



bool AreaTriggerAction::Execute(Event event)
{
    Player*  bot = ai->GetBot();
    Player* master = bot->GetPlayerbotAI()->GetMaster();

    LastMovement& movement = ai->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();
    
    uint32 triggerId = movement.lastAreaTrigger;
    movement.lastAreaTrigger = 0;

    AreaTriggerEntry const* atEntry = sAreaTriggerStore.LookupEntry(triggerId);
    if(!atEntry)
        return false;

    AreaTrigger const* at = sObjectMgr.GetAreaTrigger(triggerId);
    if (!at)
        return true;

    ai->ChangeNonCombatStrategy("-follow,+stay");
    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    bot->TeleportTo(atEntry->mapid, atEntry->x, atEntry->y, atEntry->z, 0.0f, TELE_TO_NOT_LEAVE_TRANSPORT);
    bot->SendHeartBeat(false);
    
    WorldPacket p(CMSG_AREATRIGGER);
    p << triggerId;
    p.rpos(0);
    bot->GetSession()->HandleAreaTriggerOpcode(p);

    return true;
}
