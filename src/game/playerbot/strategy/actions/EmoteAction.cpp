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

    ObjectGuid masterSelection = master->GetSelectionGuid();
    if (masterSelection)
    {
        ObjectGuid oldSelection = bot->GetSelectionGuid();
        bot->SetSelectionGuid(masterSelection);
        ai->GetBot()->HandleEmoteCommand(emote);
        bot->SetSelectionGuid(oldSelection);
    }
    else
        ai->GetBot()->HandleEmoteCommand(emote);

    return true;
}

void EmoteAction::InitEmotes()
{
    emotes["applaud"] = EMOTE_STATE_APPLAUD;
    emotes["attackbow"] = EMOTE_ONESHOT_ATTACKBOW;
    emotes["attackoff"] = EMOTE_ONESHOT_ATTACKOFF;
    emotes["attackoffpierce"] = EMOTE_ONESHOT_ATTACKOFFPIERCE;
    emotes["attackrifle"] = EMOTE_ONESHOT_ATTACKRIFLE;
    emotes["attack_unarmed"] = EMOTE_STATE_ATTACK_UNARMED;
    emotes["at_ease"] = EMOTE_STATE_AT_EASE;
    emotes["cannibalize"] = EMOTE_STATE_CANNIBALIZE;
    emotes["cheer_nosheathe"] = EMOTE_ONESHOT_CHEER_NOSHEATHE;
    emotes["cower"] = EMOTE_ONESHOT_COWER;
    emotes["creature_special"] = EMOTE_ONESHOT_CREATURE_SPECIAL;
    emotes["dance"] = EMOTE_ONESHOT_DANCE;
    emotes["dancespecial"] = EMOTE_ONESHOT_DANCESPECIAL;
    emotes["dead"] = EMOTE_STATE_DEAD;
    emotes["dodge"] = EMOTE_ONESHOT_DODGE;
    emotes["dragonspit"] = EMOTE_ONESHOT_DRAGONSPIT;
    emotes["drown"] = EMOTE_ONESHOT_DROWN;
    emotes["drowned"] = EMOTE_STATE_DROWNED;
    emotes["eat"] = EMOTE_STATE_EAT;
    emotes["eat_nosheathe"] = EMOTE_ONESHOT_EAT_NOSHEATHE;
    emotes["emerge"] = EMOTE_ONESHOT_EMERGE;
    emotes["exclaim"] = EMOTE_STATE_EXCLAIM;
    emotes["fall"] = EMOTE_STATE_FALL;
    emotes["fishing"] = EMOTE_ONESHOT_FISHING;
    emotes["flyattack"] = EMOTE_ONESHOT_FLYATTACK1H;
    emotes["flydeath"] = EMOTE_ONESHOT_FLYDEATH;
    emotes["flyfall"] = EMOTE_STATE_FLYFALL;
    emotes["flygrab"] = EMOTE_ONESHOT_FLYGRAB;
    emotes["flygrabclosed"] = EMOTE_STATE_FLYGRABCLOSED;
    emotes["flygrabthrown"] = EMOTE_ONESHOT_FLYGRABTHROWN;
    emotes["flytalk"] = EMOTE_ONESHOT_FLYTALK;
    emotes["fly_dragonspit"] = EMOTE_ONESHOT_FLY_DRAGONSPIT;
    emotes["fly_fall"] = EMOTE_STATE_FLY_FALL;
    emotes["fly_sit_ground"] = EMOTE_STATE_FLY_SIT_GROUND;
    emotes["fly_sit_ground_down"] = EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN;
    emotes["fly_sit_ground_up"] = EMOTE_ONESHOT_FLY_SIT_GROUND_UP;
    emotes["hold_bow"] = EMOTE_STATE_HOLD_BOW;
    emotes["hold_joust"] = EMOTE_STATE_HOLD_JOUST;
    emotes["hold_rifle"] = EMOTE_STATE_HOLD_RIFLE;
    emotes["hold_thrown"] = EMOTE_STATE_HOLD_THROWN;
    emotes["jumpend"] = EMOTE_ONESHOT_JUMPEND;
    emotes["jumplandrun"] = EMOTE_ONESHOT_JUMPLANDRUN;
    emotes["jumpstart"] = EMOTE_ONESHOT_JUMPSTART;
    emotes["kneel"] = EMOTE_STATE_KNEEL;
    emotes["land"] = EMOTE_ONESHOT_LAND;
    emotes["laugh"] = EMOTE_STATE_LAUGH;
    emotes["laugh_nosheathe"] = EMOTE_ONESHOT_LAUGH_NOSHEATHE;
    emotes["liftoff"] = EMOTE_ONESHOT_LIFTOFF;
    emotes["loot"] = EMOTE_ONESHOT_LOOT;
    emotes["mount"] = EMOTE_STATE_MOUNT;
    emotes["mountspecial"] = EMOTE_ONESHOT_MOUNTSPECIAL;
    emotes["no"] = EMOTE_ONESHOT_NO;
    emotes["omnicast_ghoul"] = EMOTE_ONESHOT_OMNICAST_GHOUL;
    emotes["one_shot_stun"] = EMOTE_ONE_SHOT_STUN;
    emotes["parryh"] = EMOTE_ONESHOT_PARRY1H;
    emotes["point_nosheathe"] = EMOTE_ONESHOT_POINT_NOSHEATHE;
    emotes["ready"] = EMOTE_STATE_READY1H;
    emotes["readybow"] = EMOTE_STATE_READYBOW;
    emotes["readyjoust"] = EMOTE_STATE_READYJOUST;
    emotes["readyrifle"] = EMOTE_ONESHOT_READYRIFLE;
    emotes["readyspellomni"] = EMOTE_STATE_READYSPELLOMNI;
    emotes["readythrown"] = EMOTE_STATE_READYTHROWN;
    emotes["roar"] = EMOTE_STATE_ROAR;
    emotes["salute"] = EMOTE_ONESHOT_SALUTE;
    emotes["salute_nosheath"] = EMOTE_ONESHOT_SALUTE_NOSHEATH;
    emotes["sit_chair_high"] = EMOTE_STATE_SIT_CHAIR_HIGH;
    emotes["sit_chair_low"] = EMOTE_STATE_SIT_CHAIR_LOW;
    emotes["sit_chair_med"] = EMOTE_STATE_SIT_CHAIR_MED;
    emotes["specialunarmed"] = EMOTE_STATE_SPECIALUNARMED;
    emotes["spellcast_omni"] = EMOTE_ONESHOT_SPELLCAST_OMNI;
    emotes["spellcast_w_sound"] = EMOTE_ONESHOT_SPELLCAST_W_SOUND;
    emotes["spelleffect_hold"] = EMOTE_STATE_SPELLEFFECT_HOLD;
    emotes["spellkneelstart"] = EMOTE_STATE_SPELLKNEELSTART;
    emotes["spellprecast"] = EMOTE_STATE_SPELLPRECAST;
    emotes["spell_channel_directed"] = EMOTE_STATE_SPELL_CHANNEL_DIRECTED;
    emotes["spell_channel_omni"] = EMOTE_STATE_SPELL_CHANNEL_OMNI;
    emotes["stand_state_none"] = EMOTE_STAND_STATE_NONE;
    emotes["stealth_stand"] = EMOTE_STATE_STEALTH_STAND;
    emotes["stomp"] = EMOTE_ONESHOT_STOMP;
    emotes["strangulate"] = EMOTE_STATE_STRANGULATE;
    emotes["stun"] = EMOTE_STATE_STUN;
    emotes["stun_nosheathe"] = EMOTE_STATE_STUN_NOSHEATHE;
    emotes["submerge"] = EMOTE_ONESHOT_SUBMERGE;
    emotes["submerged"] = EMOTE_STATE_SUBMERGED;
    emotes["submerged_new"] = EMOTE_STATE_SUBMERGED_NEW;
    emotes["swim_idle"] = EMOTE_STATE_SWIM_IDLE;
    emotes["talk"] = EMOTE_STATE_TALK;
    emotes["talk_nosheathe"] = EMOTE_ONESHOT_TALK_NOSHEATHE;
    emotes["train"] = EMOTE_ONESHOT_TRAIN;
    emotes["usestanding"] = EMOTE_ONESHOT_USESTANDING;
    emotes["usestanding_nosheathe"] = EMOTE_STATE_USESTANDING_NOSHEATHE;
    emotes["walkbackwards"] = EMOTE_STATE_WALKBACKWARDS;
    emotes["wave_nosheathe"] = EMOTE_ONESHOT_WAVE_NOSHEATHE;
    emotes["whirlwind"] = EMOTE_STATE_WHIRLWIND;
    emotes["work"] = EMOTE_STATE_WORK;
    emotes["work_chopwood"] = EMOTE_ONESHOT_WORK_CHOPWOOD;
    emotes["work_mining"] = EMOTE_ONESHOT_WORK_MINING;
    emotes["yes"] = EMOTE_ONESHOT_YES;
    emotes["applaud"] = EMOTE_ONESHOT_APPLAUD;
    emotes["attack"] = EMOTE_ONESHOT_ATTACK1H;
    emotes["attackthrown"] = EMOTE_ONESHOT_ATTACKTHROWN;
    emotes["attackunarmed"] = EMOTE_ONESHOT_ATTACKUNARMED;
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
    emotes["none"] = EMOTE_STATE_NONE;
    emotes["parryshield"] = EMOTE_ONESHOT_PARRYSHIELD;
    emotes["parryunarmed"] = EMOTE_ONESHOT_PARRYUNARMED;
    emotes["point"] = EMOTE_ONESHOT_POINT;
    emotes["point"] = EMOTE_STATE_POINT;
    emotes["question"] = EMOTE_ONESHOT_QUESTION;
    emotes["ready1h"] = EMOTE_ONESHOT_READY1H;
    emotes["readybow"] = EMOTE_ONESHOT_READYBOW;
    emotes["readyunarmed"] = EMOTE_ONESHOT_READYUNARMED;
    emotes["roar"] = EMOTE_ONESHOT_ROAR;
    emotes["rude"] = EMOTE_ONESHOT_RUDE;
    emotes["sheathed"] = EMOTE_STATE_WORK_SHEATHED;
    emotes["shout"] = EMOTE_ONESHOT_SHOUT;
    emotes["shy"] = EMOTE_ONESHOT_SHY;
    emotes["sit"] = EMOTE_STATE_SIT;
    emotes["sleep"] = EMOTE_STATE_SLEEP;
    emotes["spellcast"] = EMOTE_ONESHOT_SPELLCAST;
    emotes["spellprecast"] = EMOTE_ONESHOT_SPELLPRECAST;
    emotes["stand"] = EMOTE_STATE_STAND;
    emotes["talk"] = EMOTE_ONESHOT_TALK;
    emotes["wave"] = EMOTE_ONESHOT_WAVE;
    emotes["woundcritical"] = EMOTE_ONESHOT_WOUNDCRITICAL;
    emotes["wound"] = EMOTE_ONESHOT_WOUND;
}
