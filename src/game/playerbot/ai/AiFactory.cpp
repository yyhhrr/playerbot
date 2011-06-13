#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiFactory.h"
#include "../strategy/Engine.h"

#include "../strategy/priest/PriestAiObjectContext.h"
#include "../strategy/mage/MageAiObjectContext.h"
#include "../strategy/warlock/WarlockAiObjectContext.h"
#include "../strategy/warrior/WarriorAiObjectContext.h"
#include "../strategy/shaman/ShamanAiObjectContext.h"
#include "../strategy/paladin/PaladinAiObjectContext.h"
#include "../strategy/druid/DruidAiObjectContext.h"
#include "../strategy/hunter/HunterAiObjectContext.h"
#include "../strategy/rogue/RogueAiObjectContext.h"


AiObjectContext* AiFactory::createAiObjectContext(Player* player, AiManagerRegistry* const aiRegistry)
{
    switch (player->getClass())
    {
    case CLASS_PRIEST:
        return new PriestAiObjectContext(aiRegistry);
        break;
    case CLASS_MAGE:
        return new MageAiObjectContext(aiRegistry);
        break;
    case CLASS_WARLOCK:
        return new WarlockAiObjectContext(aiRegistry);
        break;
    case CLASS_WARRIOR:
        return new WarriorAiObjectContext(aiRegistry);
        break;
    case CLASS_SHAMAN:
        return new ShamanAiObjectContext(aiRegistry);
        break;
    case CLASS_PALADIN:
        return new PaladinAiObjectContext(aiRegistry);
        break;
    case CLASS_DRUID:
        return new DruidAiObjectContext(aiRegistry);
        break;
    case CLASS_HUNTER:
        return new HunterAiObjectContext(aiRegistry);
        break;
    case CLASS_ROGUE:
        return new RogueAiObjectContext(aiRegistry);
        break;
    }
    return NULL;
}

Engine* AiFactory::createCombatEngine(Player* player, AiManagerRegistry* const facade, AiObjectContext* AiObjectContext) {
	Engine* engine = NULL;

    engine = new Engine(facade, AiObjectContext);
	switch (player->getClass())
    {
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
			engine->addStrategies("tank", "tank assist", "bhealth", "barmor", NULL);
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
	return engine;
}

Engine* AiFactory::createNonCombatEngine(Player* player, AiManagerRegistry* const facade, AiObjectContext* AiObjectContext) {
	Engine* nonCombatEngine = NULL;
    nonCombatEngine = new Engine(facade, AiObjectContext);
	switch (player->getClass())
    {
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
			nonCombatEngine->addStrategy("tank assist");
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
    nonCombatEngine->addStrategies("nc", "emote", "food", "stay", "chat", "world packet", NULL);
	return nonCombatEngine;
}

Engine* AiFactory::createDeadEngine(Player* player, AiManagerRegistry* const facade, AiObjectContext* AiObjectContext) {
    Engine* deadEngine = NULL;
    deadEngine = new Engine(facade, AiObjectContext);
   
    deadEngine->addStrategies("dead", "stay", "chat", "world packet", NULL);
    return deadEngine;
}