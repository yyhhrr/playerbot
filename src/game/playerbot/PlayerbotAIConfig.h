#pragma once

#include "../../shared/Config/Config.h"

class Player;
class PlayerbotMgr;
class ChatHandler;

class PlayerbotAIConfig
{
public:
    PlayerbotAIConfig();

public:
    bool Initialize();
    bool IsInRandomAccountList(uint32 id);

    bool enabled;
    bool allowGuildBots;
    uint32 globalCoolDown, reactDelay, teleportDelay;
    float sightDistance, spellDistance, reactDistance, grindDistance, lootDistance, fleeDistance;
    std::list<uint32> randomBotAccounts;
    uint32 criticalHealth, lowHealth, mediumHealth;

private:
    Config config;
};

#define sPlayerbotAIConfig MaNGOS::Singleton<PlayerbotAIConfig>::Instance()
