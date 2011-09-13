#include "../pchdef.h"
#include "playerbot.h"
#include "AiFactory.h"
#include "strategy/Engine.h"

#include "strategy/priest/PriestAiObjectContext.h"
#include "strategy/mage/MageAiObjectContext.h"
#include "strategy/warlock/WarlockAiObjectContext.h"
#include "strategy/warrior/WarriorAiObjectContext.h"
#include "strategy/shaman/ShamanAiObjectContext.h"
#include "strategy/paladin/PaladinAiObjectContext.h"
#include "strategy/druid/DruidAiObjectContext.h"
#include "strategy/hunter/HunterAiObjectContext.h"
#include "strategy/rogue/RogueAiObjectContext.h"
#include "../Player.h"


AiObjectContext* AiFactory::createAiObjectContext(Player* player, PlayerbotAI* ai)
{
    switch (player->getClass())
    {
    case CLASS_PRIEST:
        return new PriestAiObjectContext(ai);
        break;
    case CLASS_MAGE:
        return new MageAiObjectContext(ai);
        break;
    case CLASS_WARLOCK:
        return new WarlockAiObjectContext(ai);
        break;
    case CLASS_WARRIOR:
        return new WarriorAiObjectContext(ai);
        break;
    case CLASS_SHAMAN:
        return new ShamanAiObjectContext(ai);
        break;
    case CLASS_PALADIN:
        return new PaladinAiObjectContext(ai);
        break;
    case CLASS_DRUID:
        return new DruidAiObjectContext(ai);
        break;
    case CLASS_HUNTER:
        return new HunterAiObjectContext(ai);
        break;
    case CLASS_ROGUE:
        return new RogueAiObjectContext(ai);
        break;
    }
    return NULL;
}

void AiFactory::AddDefaultCombatStrategies(Player* player, Engine* engine)
{
    map<uint32, int32> tabs;
    for (uint32 i = 0; i < uint32(3); i++)
        tabs[i] = 0;

    uint8 activeSpec = player->GetActiveSpec();
    PlayerTalentMap talents = player->GetTalentMap(activeSpec);
    for (PlayerTalentMap::iterator iter = talents.begin(); iter != talents.end(); ++iter)
    {
        if (iter->second.state == PLAYERSPELL_REMOVED)
            continue;

        TalentEntry const* talentInfo = iter->second.talentEntry;
        if (!talentInfo)
            continue;

        TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
        if (!talentTabInfo)
            continue;

        if ((player->getClassMask() & talentTabInfo->ClassMask) == 0)
            continue;

        tabs[talentTabInfo->tabpage]++;
    }
    int tab = -1, max = 0;
    for (uint32 i = 0; i < uint32(3); i++)
    {
        if (tab == -1 || max < tabs[i])
        {
            tab = i;
            max = tabs[i];
        }
    }
    
    switch (player->getClass()){
        case CLASS_PRIEST:
            engine->addStrategy(tab == 2 ? "dps" : "heal");
            break;
        case CLASS_MAGE:
            engine->addStrategy(tab == 1 ? "fire" : "frost");
            break;
        case CLASS_WARRIOR:
            engine->addStrategy(tab == 2 ? "tank" : "dps");
            break;
        case CLASS_SHAMAN:
            engine->addStrategy(tab == 2 ? "heal" : "dps");
            break;
        case CLASS_PALADIN:
            engine->addStrategy(tab == 1 ? "tank" : "dps");
            engine->addStrategy("barmor");
            break;
        case CLASS_DRUID:
            engine->addStrategy(tab == 0 ? "caster" : "bear");
            break;
        case CLASS_HUNTER:
            engine->addStrategy("bdps");
        case CLASS_ROGUE:
        case CLASS_WARLOCK:
            engine->addStrategy("dps");
            break;
    }
    engine->addStrategies("flee", "attack weak", "racials", "chat", "world packet", NULL);
}

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* engine = new Engine(facade, AiObjectContext);
    AddDefaultCombatStrategies(player, engine);
	return engine;
}

void AiFactory::AddDefaultNonCombatStrategies(Player* player, Engine* nonCombatEngine)
{
    switch (player->getClass()){
        case CLASS_PALADIN:
            nonCombatEngine->addStrategy("bmana");
            break;
        case CLASS_HUNTER:
            nonCombatEngine->addStrategy("bspeed");
            break;
    }
    nonCombatEngine->addStrategies("nc", "attack weak", "emote", "food", "stay", "chat", "world packet", "quest", "loot", "gather", NULL);
}

Engine* AiFactory::createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* nonCombatEngine = new Engine(facade, AiObjectContext);
    AddDefaultNonCombatStrategies(player, nonCombatEngine);
	return nonCombatEngine;
}

void AiFactory::AddDefaultDeadStrategies(Engine* deadEngine)
{
    deadEngine->addStrategies("dead", "stay", "chat", "world packet", NULL);
}

Engine* AiFactory::createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
    Engine* deadEngine = new Engine(facade, AiObjectContext);
    AddDefaultDeadStrategies(deadEngine);
    return deadEngine;
}
