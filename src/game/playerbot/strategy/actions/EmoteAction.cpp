#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "EmoteAction.h"

using namespace ai;

map<string, uint32> EmoteAction::emotes;

bool EmoteAction::Execute(Event event)
{
    if (emotes.empty())
        InitEmotes();

    uint32 emote = 0;

    string param = event.getParam();
	if (param.empty() || emotes.find(param) == emotes.end())
    {
        int index = rand() % emotes.size();
		for (map<string, uint32>::iterator i = emotes.begin(); i != emotes.end() && index; ++i, --index)
			emote = i->second;
    }
    else
    {
        emote = emotes[param];
    }

    Player* master = GetMaster();
	if (master)
	{
        ObjectGuid masterSelection = master->GetSelectionGuid();
        if (masterSelection)
        {
            ObjectGuid oldSelection = bot->GetSelectionGuid();
            bot->SetSelectionGuid(masterSelection);
            ai->GetBot()->HandleEmoteCommand(emote);
            bot->SetSelectionGuid(oldSelection);
            return true;
        }
	}

    ai->GetBot()->HandleEmoteCommand(emote);
    return true;
}

void EmoteAction::InitEmotes()
{
    emotes["dance"] = EMOTE_ONESHOT_DANCE;
    emotes["drown"] = EMOTE_ONESHOT_DROWN;
    emotes["land"] = EMOTE_ONESHOT_LAND;
    emotes["laugh_nosheathe"] = EMOTE_ONESHOT_LAUGH_NOSHEATHE;
    emotes["liftoff"] = EMOTE_ONESHOT_LIFTOFF;
    emotes["loot"] = EMOTE_ONESHOT_LOOT;
    emotes["no"] = EMOTE_ONESHOT_NO;
    emotes["point_nosheathe"] = EMOTE_ONESHOT_POINT_NOSHEATHE;
    emotes["roar"] = EMOTE_STATE_ROAR;
    emotes["salute"] = EMOTE_ONESHOT_SALUTE;
    emotes["stomp"] = EMOTE_ONESHOT_STOMP;
    emotes["train"] = EMOTE_ONESHOT_TRAIN;
    emotes["yes"] = EMOTE_ONESHOT_YES;
    emotes["applaud"] = EMOTE_ONESHOT_APPLAUD;
    emotes["battleroar"] = EMOTE_ONESHOT_BATTLEROAR;
    emotes["beg"] = EMOTE_ONESHOT_BEG;
    emotes["bow"] = EMOTE_ONESHOT_BOW;
    emotes["cheer"] = EMOTE_ONESHOT_CHEER;
    emotes["chicken"] = EMOTE_ONESHOT_CHICKEN;
    emotes["cry"] = EMOTE_ONESHOT_CRY;
    emotes["dance"] = EMOTE_STATE_DANCE;
    emotes["eat"] = EMOTE_ONESHOT_EAT;
    emotes["exclamation"] = EMOTE_ONESHOT_EXCLAMATION;
    emotes["flex"] = EMOTE_ONESHOT_FLEX;
    emotes["kick"] = EMOTE_ONESHOT_KICK;
    emotes["kiss"] = EMOTE_ONESHOT_KISS;
    emotes["kneel"] = EMOTE_ONESHOT_KNEEL;
    emotes["laugh"] = EMOTE_ONESHOT_LAUGH;
    emotes["parryshield"] = EMOTE_ONESHOT_PARRYSHIELD;
    emotes["parryunarmed"] = EMOTE_ONESHOT_PARRYUNARMED;
    emotes["point"] = EMOTE_ONESHOT_POINT;
    emotes["question"] = EMOTE_ONESHOT_QUESTION;
    emotes["ready1h"] = EMOTE_ONESHOT_READY1H;
    emotes["readybow"] = EMOTE_ONESHOT_READYBOW;
    emotes["readyunarmed"] = EMOTE_ONESHOT_READYUNARMED;
    emotes["roar"] = EMOTE_ONESHOT_ROAR;
    emotes["rude"] = EMOTE_ONESHOT_RUDE;
    emotes["shout"] = EMOTE_ONESHOT_SHOUT;
    emotes["shy"] = EMOTE_ONESHOT_SHY;
    emotes["sleep"] = EMOTE_STATE_SLEEP;
    emotes["talk"] = EMOTE_ONESHOT_TALK;
    emotes["wave"] = EMOTE_ONESHOT_WAVE;
    emotes["woundcritical"] = EMOTE_ONESHOT_WOUNDCRITICAL;
    emotes["wound"] = EMOTE_ONESHOT_WOUND;
}
