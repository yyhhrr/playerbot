#include "Config/Config.h"
#include "../pchdef.h"
#include "playerbot.h"
#include "strategy/values/SharedValueContext.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotFactory.h"
#include "../AccountMgr.h"
#include "../ObjectMgr.h"
#include "../../shared/Database/DatabaseEnv.h"
#include "PlayerbotAI.h"
#include "../Player.h"

RandomPlayerbotMgr::RandomPlayerbotMgr(Player* const master) : PlayerbotAIBase(),  master(master)
{
    account = sObjectMgr.GetPlayerAccountIdByGUID(master->GetObjectGuid());
}

RandomPlayerbotMgr::~RandomPlayerbotMgr()
{
}

void RandomPlayerbotMgr::UpdateAIInternal(uint32 elapsed)
{
    SetNextCheckDelay(sPlayerbotAIConfig.randomBotUpdateInterval * 1000);

    if (!sPlayerbotAIConfig.randomBotAutologin)
        return;

    sLog.outBasic("Processing random bots for account %d...", account);

    int maxAllowedBotCount = GetEventValue(0, "bot_count");
    if (!maxAllowedBotCount)
    {
        maxAllowedBotCount = urand(sPlayerbotAIConfig.minRandomBots, sPlayerbotAIConfig.maxRandomBots);
        SetEventValue(0, "bot_count", maxAllowedBotCount, sPlayerbotAIConfig.randomBotCountChangeInterval);
    }

    list<uint32> bots = GetBots();
    int botCount = bots.size();
    while (botCount++ < maxAllowedBotCount)
    {
        uint32 bot = AddRandomBot();
        if (bot)
        {
            bots.push_back(bot);
        }
    }

    for (list<uint32>::iterator i = bots.begin(); i != bots.end(); ++i)
    {
        uint32 bot = *i;
        ProcessBot(bot);
    }

}

uint32 RandomPlayerbotMgr::AddRandomBot()
{
    vector<uint32> bots = GetFreeBots();
    if (bots.size() == 0)
        return 0;

    int index = urand(0, bots.size() - 1);
    uint32 bot = bots[index];
    SetEventValue(bot, "add", 1, urand(sPlayerbotAIConfig.minRandomBotInWorldTime, sPlayerbotAIConfig.maxRandomBotInWorldTime));
    sLog.outBasic("Bot %d added for account %d", bot, account);
    return bot;
}

void RandomPlayerbotMgr::ProcessBot(uint32 bot)
{
    PlayerbotMgr* mgr = master->GetPlayerbotMgr();

    uint32 isValid = GetEventValue(bot, "add");
    if (!isValid)
    {
		Player* player = mgr->GetPlayerBot(bot);
		if (!player || !player->GetGroup())
		{
			if (mgr->GetPlayerBot(bot))
				mgr->LogoutPlayerBot(bot);

			sLog.outBasic("Bot %d expired for account %d", bot, account);
			SetEventValue(bot, "add", 0, 0);
		}
        return;
    }

    if (!mgr->GetPlayerBot(bot))
    {
        sLog.outBasic("Bot %d logged in for account %d", bot, account);
        mgr->AddPlayerBot(bot, master->GetSession());
        return;
    }

    Player* player = mgr->GetPlayerBot(bot);
    if (!player)
        return;

    PlayerbotAI* ai = player->GetPlayerbotAI();
    if (!ai)
        return;

    if (ai->IsOpposing(master) && urand(0, 100) <= sPlayerbotAIConfig.pvpChance &&
            !master->GetInstanceId() && master->IsAllowedDamageInArea(player))
    {
        ai->DoPvpAttack();
    }

	if (!player->GetGroup() && urand(0, 100) <= sPlayerbotAIConfig.randomTeleportChance && !player->isInCombat())
    {
        ai->RandomTeleport();
    }

    sLog.outBasic("Bot %d processed in for account %d", bot, account);
}


list<uint32> RandomPlayerbotMgr::GetBots()
{
    list<uint32> bots;

    QueryResult* results = CharacterDatabase.PQuery(
            "select `bot` from ai_playerbot_random_bots where owner = '%u' and event = 'add'", account);

    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 bot = fields[0].GetUInt32();
            bots.push_back(bot);
        } while (results->NextRow());
        delete results;
    }

    return bots;
}

vector<uint32> RandomPlayerbotMgr::GetFreeBots()
{
    set<uint32> bots;

    QueryResult* results = CharacterDatabase.PQuery(
            "select `bot` from ai_playerbot_random_bots where event = 'add'");

    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 bot = fields[0].GetUInt32();
            bots.insert(bot);
        } while (results->NextRow());
        delete results;
    }

    vector<uint32> guids;
    for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); i++)
    {
        uint32 accountId = *i;
        if (!sAccountMgr.GetCharactersCount(accountId))
            continue;

        QueryResult *result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account = '%u'", accountId);
        if (!result)
            continue;

        do
        {
            Field* fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            if (bots.find(guid) == bots.end())
                guids.push_back(guid);
        } while (result->NextRow());
        delete result;
    }


    return guids;
}

uint32 RandomPlayerbotMgr::GetEventValue(uint32 bot, string event)
{
    uint32 value = 0;

    QueryResult* results = CharacterDatabase.PQuery(
            "select `value`, `time`, validIn from ai_playerbot_random_bots where owner = '%u' and bot = '%u' and event = '%s'",
            account, bot, event.c_str());

    if (results)
    {
        Field* fields = results->Fetch();
        value = fields[0].GetUInt32();
        uint32 lastChangeTime = fields[1].GetUInt32();
        uint32 validIn = fields[2].GetUInt32();
        if ((time(0) - lastChangeTime) >= validIn)
            value = 0;
        delete results;
    }

    return value;
}

uint32 RandomPlayerbotMgr::SetEventValue(uint32 bot, string event, uint32 value, uint32 validIn)
{
    CharacterDatabase.PExecute("delete from ai_playerbot_random_bots where owner = '%u' and bot = '%u' and event = '%s'",
            account, bot, event.c_str());
    if (value)
    {
        CharacterDatabase.PExecute(
                "insert into ai_playerbot_random_bots (owner, bot, `time`, validIn, event, `value`) values ('%u', '%u', '%u', '%u', '%s', '%u')",
                account, bot, (uint32)time(0), validIn, event.c_str(), value);
    }

    return value;
}
