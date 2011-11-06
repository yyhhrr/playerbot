#include "../pchdef.h"
#include "PlayerbotAIConfig.h"
#include "Policies/SingletonImp.h"
#include "playerbot.h"

using namespace std;

INSTANTIATE_SINGLETON_1(PlayerbotAIConfig);

PlayerbotAIConfig::PlayerbotAIConfig()
{
}

bool PlayerbotAIConfig::Initialize()
{
    sLog.outString("Initializing AI Playerbot by ike3, based on the original Playerbot by blueboy");

    if (!config.SetSource("aiplayerbot.conf"))
    {
        sLog.outString("AI Playerbot is Disabled. Unable to open configuration file aiplayerbot.conf");
        return false;
    }

    enabled = config.GetBoolDefault("AiPlayerbot.Enabled", true);
	if (!enabled)
		sLog.outString("AI Playerbot is Disabled in aiplayerbot.conf");
    
    globalCoolDown = (uint32) config.GetIntDefault("AiPlayerbot.GlobalCooldown", 1500);
    teleportDelay = config.GetIntDefault("AiPlayerbot.TeleportDelay", 10000);
    reactDelay = (uint32) config.GetIntDefault("AiPlayerbot.ReactDelay", 250);
    
    sightDistance = config.GetFloatDefault("AiPlayerbot.SightDistance", 40.0f);
    spellDistance = config.GetFloatDefault("AiPlayerbot.SpellDistance", 25.0f);
    reactDistance = config.GetFloatDefault("AiPlayerbot.ReactDistance", 100.0f);
    grindDistance = config.GetFloatDefault("AiPlayerbot.GrindDistance", 50.0f);
    lootDistance = config.GetFloatDefault("AiPlayerbot.LootDistance", 20.0f);
    fleeDistance = config.GetFloatDefault("AiPlayerbot.FleeDistance", 15.0f);
    
    criticalHealth = config.GetIntDefault("AiPlayerbot.CriticalHealth", 25);
    lowHealth = config.GetIntDefault("AiPlayerbot.LowHealth", 45);
    mediumHealth = config.GetIntDefault("AiPlayerbot.MediumHealth", 65);
    almostFullHealth = config.GetIntDefault("AiPlayerbot.AlmostFullHealth", 85);
    lowMana = config.GetIntDefault("AiPlayerbot.LowMana", 15);
    
    pvpChance = config.GetIntDefault("AiPlayerbot.PvpChance", 5);
    randomGearQuality = config.GetIntDefault("AiPlayerbot.RandomGearQuality", ITEM_QUALITY_RARE);

    iterationsPerTick = config.GetIntDefault("AiPlayerbot.IterationsPerTick", 10);

    allowGuildBots = config.GetBoolDefault("AiPlayerbot.AllowGuildBots", true);
    string accountStr = config.GetStringDefault("AiPlayerbot.RandomBotAccounts", "");
    vector<string> accounts = split(accountStr, ',');
    for (vector<string>::iterator i = accounts.begin(); i != accounts.end(); i++)
    {
        uint32 id = atoi((*i).c_str());
        if (!id)
            continue;
        randomBotAccounts.push_back(id);
    }

    sLog.outString("AI Playerbot configuration loaded");
    return true;
}


bool PlayerbotAIConfig::IsInRandomAccountList(uint32 id)
{
    return find(randomBotAccounts.begin(), randomBotAccounts.end(), id) != randomBotAccounts.end();
}
