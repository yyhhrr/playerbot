#include "Config/Config.h"
#include "../pchdef.h"
#include "playerbot.h"
#include "strategy/values/SharedValueContext.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotFactory.h"
#include "../AccountMgr.h"


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

    virtual void UpdateAIInternal(uint32 elapsed)
    {
        sharedValues.Update();
    }

    void Clear()
    {
        sharedValues.Clear();
    }

private:
    SharedValueContext sharedValues;
};

PlayerbotMgr::PlayerbotMgr(Player* const master) : PlayerbotAIBase(),  m_master(master) , sharedAi(NULL)
{
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

void PlayerbotMgr::UpdateAIInternal(uint32 elapsed)
{
    if (sharedAi)
        sharedAi->UpdateAI(elapsed);

    SetNextCheckDelay(sPlayerbotAIConfig.reactDelay);
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
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleMasterOutgoingPacket(packet);
    }
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

        ResetSharedAi();

        WorldSession * botWorldSessionPtr = bot->GetSession();
        m_playerBots.erase(guid);    // deletes bot player ptr inside this WorldSession PlayerBotMap
        botWorldSessionPtr->LogoutPlayer(true); // this will delete the bot Player object and PlayerbotAI object
        delete botWorldSessionPtr;  // finally delete the bot's WorldSession
    }
}

void PlayerbotMgr::RandomizePlayerBot(uint64 guid, uint32 level)
{
    Player* bot = GetPlayerBot(guid);
    if (!bot)
        return;

    PlayerbotFactory factory(bot, level);
    factory.Randomize();
}

Player* PlayerbotMgr::GetPlayerBot(uint64 playerGuid) const
{
    PlayerBotMap::const_iterator it = m_playerBots.find(playerGuid);
    return (it == m_playerBots.end()) ? 0 : it->second;
}

void PlayerbotMgr::OnBotLogin(Player * const bot)
{
    ResetSharedAi();

    PlayerbotAI* ai = new PlayerbotAI(this, bot, ((SharedPlayerbotAI*)sharedAi)->GetSharedValues());
    bot->SetPlayerbotAI(ai);

    m_playerBots[bot->GetObjectGuid().GetRawValue()] = bot;

    ObjectGuid masterGuid = m_master->GetObjectGuid();
    if (m_master->GetGroup() &&
        ! m_master->GetGroup()->IsLeader(masterGuid))
        m_master->GetGroup()->ChangeLeader(masterGuid);

    ai->OnBotLogin();
    ai->TellMaster("Hello!");
}

bool processBotCommand(WorldSession* session, string cmdStr, ObjectGuid guid)
{
    if (!sPlayerbotAIConfig.enabled || guid.IsEmpty() || (guid == session->GetPlayer()->GetObjectGuid()))
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
    else if (cmdStr == "init")
    {
        Player* bot = mgr->GetPlayerBot(guid.GetRawValue());
        if (!bot)
            return false;

        uint32 account = sObjectMgr.GetPlayerAccountIdByGUID(bot->GetObjectGuid());
        if (session->GetSecurity() >= SEC_GAMEMASTER || sPlayerbotAIConfig.IsInRandomAccountList(account))
            mgr->RandomizePlayerBot(guid.GetRawValue(), session->GetPlayer()->getLevel());
    }
    else if (cmdStr == "pvp")
    {
        Player* bot = mgr->GetPlayerBot(guid.GetRawValue());
        if (!bot)
            return false;

        uint32 account = sObjectMgr.GetPlayerAccountIdByGUID(bot->GetObjectGuid());
        if (session->GetSecurity() >= SEC_GAMEMASTER || sPlayerbotAIConfig.IsInRandomAccountList(account))
            bot->GetPlayerbotAI()->DoPvpAttack();
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
        PSendSysMessage("usage: add/init/remove PLAYERNAME or option or option=value");
        SetSentErrorMessage(true);
        return false;
    }

    char *cmd = strtok ((char*)args, " ");
    char *charname = strtok (NULL, " ");
    if (!cmd || !charname)
    {
        PSendSysMessage("usage: add/init/remove PLAYERNAME or option or option=value");
        SetSentErrorMessage(true);
        return false;
    }

    std::string cmdStr = cmd;
    std::string charnameStr = charname;

    if (cmdStr == "option" && m_session->GetSecurity() >= SEC_GAMEMASTER)
    {
        if (charnameStr.find("=") == string::npos)
        {
            string value = sPlayerbotAIConfig.GetValue(charnameStr);
            ostringstream out; out << charnameStr << " = " << value;
            PSendSysMessage(out.str().c_str());
        }
        else
        {
            string value = charnameStr.substr(charnameStr.find("=") + 1);
            string option = charnameStr.substr(0, charnameStr.find("="));
            sPlayerbotAIConfig.SetValue(option, value);
            ostringstream out; out << charnameStr << " set to " << value;
            PSendSysMessage(out.str().c_str());
        }
        return true;
    }

    Player* player = m_session->GetPlayer();

    // create the playerbot manager if it doesn't already exist
    PlayerbotMgr* mgr = player->GetPlayerbotMgr();
    if (!mgr)
    {
        mgr = new PlayerbotMgr(player);
        player->SetPlayerbotMgr(mgr);
    }

    if (charnameStr == "?" && cmdStr == "add")
    {
        PSendSysMessage("Processing random bot...");
        ObjectGuid guid = PlayerbotFactory::GetRandomBot();
        if (guid)
            mgr->AddPlayerBot(guid, m_session);
        else
            PSendSysMessage("No allowed random bots found");

        PSendSysMessage("Command %s processed", cmdStr.c_str());
    }
    else if (charnameStr == "*")
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
        PSendSysMessage("Command %s processed", cmdStr.c_str());
        return res;
    }

    bool res = true;
    vector<string> chars = split(charnameStr, ',');
    for (vector<string>::iterator i = chars.begin(); i != chars.end(); i++)
    {
        string s = *i;
        PSendSysMessage("Processing bot %s...", s.c_str());

        uint32 accountId = mgr->GetAccountId(s);
        if (accountId)
        {
            QueryResult* results = CharacterDatabase.PQuery(
                "SELECT name FROM characters WHERE account = '%u'",
                accountId);
            if (results)
            {
                do
                {
                    Field* fields = results->Fetch();
                    string charName = fields[0].GetCppString();
					if (!mgr->ProcessBot(charName, cmdStr))
					{
					    res = false;
						PSendSysMessage("Error processing bot command for %s", charName.c_str());
						SetSentErrorMessage(true);
					}

                } while (results->NextRow());

                delete results;
            }
        }
        else
        {
            if (!mgr->ProcessBot(s, cmdStr))
            {
                PSendSysMessage("Error processing bot command for %s", s.c_str());
                SetSentErrorMessage(true);
                res = false;
            }
        }
	}

    PSendSysMessage("Command %s processed", cmdStr.c_str());
    return res;
}

uint32 PlayerbotMgr::GetAccountId(string name)
{
    uint32 accountId = 0;

    QueryResult *results = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s'", name.c_str());
    if(results)
    {
        Field* fields = results->Fetch();
        accountId = fields[0].GetUInt32();
        delete results;
    }

    return accountId;
}

bool PlayerbotMgr::ProcessBot(string name, string cmdStr)
{
    ObjectGuid member = sObjectMgr.GetPlayerGuidByName(name);
	if (member != GetMaster()->GetObjectGuid())
    {
		return processBotCommand(GetMaster()->GetSession(), cmdStr, member);
    }
    return false;
}

void PlayerbotMgr::SaveToDB()
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->SaveToDB();
    }
}

void PlayerbotMgr::ResetSharedAi()
{
    if (sharedAi)
        ((SharedPlayerbotAI*)sharedAi)->Clear();
    else
        sharedAi = new SharedPlayerbotAI();
}
