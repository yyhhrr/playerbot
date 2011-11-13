#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ReadyCheckAction.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool ReadyCheckAction::Execute(Event event)
{
    WorldPacket &p = event.getPacket();
	ObjectGuid player;
	p.rpos(0);
    if (!p.empty())
        p >> player;
    
	if (player == bot->GetObjectGuid())
        return false;

	bool ready = ReadyCheck();

	if (!ready)
	    ai->ChangeStrategy("+ready check", BOT_STATE_NON_COMBAT);

	return ready;
}

bool ReadyCheckAction::ReadyCheck()
{
    bool health = AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig.almostFullHealth;
    bool mana = !AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.almostFullHealth;
    bool distance = bot->GetDistance(master) <= sPlayerbotAIConfig.sightDistance;

    if (!health || !mana || !distance)
        return false;

    WorldPacket* const packet = new WorldPacket(MSG_RAID_READY_CHECK);
    *packet << bot->GetObjectGuid();
    *packet << uint8(1);
    bot->GetSession()->QueuePacket(packet);

    ai->ChangeStrategy("-ready check", BOT_STATE_NON_COMBAT);

    return true;
}

bool FinishReadyCheckAction::Execute(Event event)
{
    return ReadyCheck();
}
