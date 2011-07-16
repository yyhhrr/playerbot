#include "Config/Config.h"
#include "../pchdef.h"
#include "playerbot.h"
#include "strategy/values/SharedValueContext.h"


class LoginQueryHolder;
class CharacterHandler;

class SharedPlayerbotAI : public PlayerbotAIBase
{
public:
    SharedPlayerbotAI() : PlayerbotAIBase() { }
    virtual ~SharedPlayerbotAI() { }

public:
    SharedValueContext* GetSharedValues() 
    {
        return &sharedValues; 
    }

    virtual void UpdateAI(uint32 elapsed)
    {
        sharedValues.Update();
    }

private:
    SharedValueContext sharedValues;
};

PlayerbotMgr::PlayerbotMgr(Player* const master) : PlayerbotAIBase(),  m_master(master) , sharedAi(NULL)
{
    // load config variables
	m_confDisableBots = sConfig.GetBoolDefault( "PlayerbotAI.DisableBots", false );
    m_confDebugWhisper = sConfig.GetBoolDefault( "PlayerbotAI.DebugWhisper", false );
    m_confFollowDistance[0] = sConfig.GetFloatDefault( "PlayerbotAI.FollowDistanceMin", 0.5f );
    m_confFollowDistance[1] = sConfig.GetFloatDefault( "PlayerbotAI.FollowDistanceMin", 1.0f );

    for (uint32 spellId = 0; spellId < sSpellStore.GetNumRows(); spellId++)
        sSpellStore.LookupEntry(spellId);
}

PlayerbotMgr::~PlayerbotMgr() 
{
    LogoutAllBots();
    if (sharedAi)
    {
        delete sharedAi;
        sharedAi = NULL;
    }
}

void PlayerbotMgr::UpdateAI(const uint32 p_time) 
{
    if (!CanUpdateAI())
        return;

    if (sharedAi) 
        sharedAi->UpdateAI(p_time);

    SetNextCheckDelay(GLOBAL_COOLDOWN);
}

void PlayerbotMgr::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleMasterIncomingPacket(packet);
    }

    switch (packet.GetOpcode())
    {
        // if master is logging out, log out all bots
        case CMSG_LOGOUT_REQUEST:
        {
            LogoutAllBots();
            return;
        }
    }
}
void PlayerbotMgr::HandleMasterOutgoingPacket(const WorldPacket& packet)
{
}

void PlayerbotMgr::LogoutAllBots()
{
    while (true)
    {
        PlayerBotMap::const_iterator itr = GetPlayerBotsBegin();
        if (itr == GetPlayerBotsEnd()) break;
        Player* bot= itr->second;
        LogoutPlayerBot(bot->GetObjectGuid().GetRawValue());
    }
}

// Playerbot mod: logs out a Playerbot.
void PlayerbotMgr::LogoutPlayerBot(uint64 guid)
{
    Player* bot= GetPlayerBot(guid);
    if (bot)
    {
        bot->GetPlayerbotAI()->TellMaster("Goodbue!");

        WorldSession * botWorldSessionPtr = bot->GetSession();
        m_playerBots.erase(guid);    // deletes bot player ptr inside this WorldSession PlayerBotMap
        botWorldSessionPtr->LogoutPlayer(true); // this will delete the bot Player object and PlayerbotAI object
        delete botWorldSessionPtr;  // finally delete the bot's WorldSession
    }
}

Player* PlayerbotMgr::GetPlayerBot(uint64 playerGuid) const
{
    PlayerBotMap::const_iterator it = m_playerBots.find(playerGuid);
    return (it == m_playerBots.end()) ? 0 : it->second;
}

void PlayerbotMgr::OnBotLogin(Player * const bot)
{
    if (!sharedAi)
        sharedAi = new SharedPlayerbotAI();

    PlayerbotAI* ai = new PlayerbotAI(this, bot, ((SharedPlayerbotAI*)sharedAi)->GetSharedValues());
    bot->SetPlayerbotAI(ai);

    m_playerBots[bot->GetObjectGuid().GetRawValue()] = bot;

    ObjectGuid masterGuid = m_master->GetObjectGuid();
    if (m_master->GetGroup() && 
        ! m_master->GetGroup()->IsLeader(masterGuid))
        m_master->GetGroup()->ChangeLeader(masterGuid);

    ai->TellMaster("Hello!");
}

bool processBotCommand(WorldSession* session, string cmdStr, ObjectGuid guid)
{
    if (guid.IsEmpty() || (guid == session->GetPlayer()->GetObjectGuid()))
        return false;

    PlayerbotMgr* mgr = session->GetPlayer()->GetPlayerbotMgr();

    if (cmdStr == "add" || cmdStr == "login")
    {
        if (mgr->GetPlayerBot(guid.GetRawValue())) 
            return false;
        
        mgr->AddPlayerBot(guid.GetRawValue(), session);
    }
    else if (cmdStr == "remove" || cmdStr == "logout")
    {
        if (! mgr->GetPlayerBot(guid.GetRawValue()))
            return false;
        
        mgr->LogoutPlayerBot(guid.GetRawValue());
    }

    return true;
}

bool ChatHandler::HandlePlayerbotCommand(char* args)
{
	if(sConfig.GetBoolDefault("PlayerbotAI.DisableBots", false))
	{
		PSendSysMessage("|cffff0000Playerbot system is currently disabled!");
        SetSentErrorMessage(true);
        return false;
	}

    if (! m_session)
    {
        PSendSysMessage("You may only add bots from an active session");
        SetSentErrorMessage(true);
        return false;
    }

    if (!*args)
    {
        PSendSysMessage("usage: add PLAYERNAME  or  remove PLAYERNAME");
        SetSentErrorMessage(true);
        return false;
    }

    char *cmd = strtok ((char*)args, " ");
    char *charname = strtok (NULL, " ");
    if (!cmd || !charname)
    {
        PSendSysMessage("usage: add PLAYERNAME  or  remove PLAYERNAME");
        SetSentErrorMessage(true);
        return false;
    }

    std::string cmdStr = cmd;
    std::string charnameStr = charname;

    Player* player = m_session->GetPlayer();

    // create the playerbot manager if it doesn't already exist
    PlayerbotMgr* mgr = player->GetPlayerbotMgr();
    if (!mgr)
    {
        mgr = new PlayerbotMgr(player);
        player->SetPlayerbotMgr(mgr);
    }

    if (charnameStr == "*")
    {
        Group* group = player->GetGroup();
        if (!group)
        {
            PSendSysMessage("you must be in group");
            SetSentErrorMessage(true);
            return false;
        }

        bool res = true;
        Group::MemberSlotList slots = group->GetMemberSlots();
        for (Group::member_citerator i = slots.begin(); i != slots.end(); i++) 
        {
			ObjectGuid member = i->guid;
			
			if (member == m_session->GetPlayer()->GetObjectGuid())
				continue;

            PSendSysMessage("Processing bot %s...", i->name.c_str());
            if (!processBotCommand(m_session, cmdStr, member))
            {
                PSendSysMessage("Error processing bot command for %s", i->name.c_str());
                SetSentErrorMessage(true);
                res = false;
            }
        }
        return res;
    }

    bool res = true;
    vector<string> chars = split(charnameStr, ',');
    for (vector<string>::iterator i = chars.begin(); i != chars.end(); i++)
    {
        string s = *i;
        ObjectGuid member = sObjectMgr.GetPlayerGuidByName(s);
        if (member == m_session->GetPlayer()->GetObjectGuid())
            continue;

        PSendSysMessage("Processing bot %s...", s.c_str());
        res &= processBotCommand(m_session, cmdStr, member);
        if (!res)
        {
            PSendSysMessage("Error processing bot command for %s", s.c_str());
            SetSentErrorMessage(true);
        }
    }
    return res;
}

void PlayerbotMgr::SaveToDB()
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->SaveToDB();
    }
}