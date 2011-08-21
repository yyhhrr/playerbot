#include "../pchdef.h"
#include "PlayerbotAIConfig.h"
#include "Policies/SingletonImp.h"

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

    allowGuildBots = config.GetBoolDefault("AiPlayerbot.AllowGuildBots", true);
    globalCoolDown = (uint32) config.GetIntDefault("AiPlayerbot.GlobalCooldown", 1000);
    teleportDelay = config.GetIntDefault("AiPlayerbot.TeleportDelay", 10000);
    reactDelay = (uint32) config.GetIntDefault("AiPlayerbot.ReactDelay", 100);
    sightDistance = config.GetIntDefault("AiPlayerbot.SightDistance", 40.0f);
    spellDistance = config.GetFloatDefault("AiPlayerbot.SpellDistance", 25.0f);
    reactDistance = config.GetFloatDefault("AiPlayerbot.ReactDistance", 100.0f);
    grindDistance = config.GetFloatDefault("AiPlayerbot.GrindDistance", 50.0f);
    lootDistance = config.GetFloatDefault("AiPlayerbot.LootDistance", 20.0f);

    sLog.outString("AI Playerbot configuration loaded");
    return true;
}
