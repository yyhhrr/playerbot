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
    switch (player->getClass()){
        case CLASS_PRIEST:
            engine->addStrategies("heal", "dps assist", NULL);
            break;
        case CLASS_MAGE:
            engine->addStrategies("frost", "dps assist", NULL);
            break;
        case CLASS_WARLOCK:
            engine->addStrategies("dps", "dps assist", NULL);
            break;
        case CLASS_WARRIOR:
            engine->addStrategies("tank", "tank assist", NULL);
            break;
        case CLASS_SHAMAN:
            engine->addStrategies("heal", "dps assist", NULL);
            break;
        case CLASS_PALADIN:
            engine->addStrategies("tank", "tank assist", "barmor", NULL);
            break;
        case CLASS_DRUID:
            engine->addStrategies("bear", "tank assist", NULL);
            break;
        case CLASS_HUNTER:
            engine->addStrategies("dps", "dps assist", "bdps", NULL);
            break;
        case CLASS_ROGUE:
            engine->addStrategies("dps", "dps assist", NULL);
            break;
    }
    engine->addStrategy("racials");
}

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* engine = new Engine(facade, AiObjectContext);
    AddDefaultCombatStrategies(player, engine);
	return engine;
}

void AiFactory::AddDefaultNonCombatStrategies(Player* player, Engine* nonCombatEngine)
{
    switch (player->getClass()){
        case CLASS_PRIEST:
            nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_MAGE:
            nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_WARLOCK:
            nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_WARRIOR:
            nonCombatEngine->addStrategy("tank assist");
            break;
        case CLASS_SHAMAN:
            nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_PALADIN:
            nonCombatEngine->addStrategies("tank assist", "bmana", NULL);
            break;
        case CLASS_DRUID:
            nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_HUNTER:
            nonCombatEngine->addStrategies("dps assist", "bspeed", NULL);
            break;
        case CLASS_ROGUE:
            nonCombatEngine->addStrategy("dps assist");
            break;
    }
    nonCombatEngine->addStrategies("nc", "emote", "food", "stay", "chat", "world packet", "quest", "loot", "gather", NULL);
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
