#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiFactory.h"
#include "../strategy/Engine.h"

#include "../strategy/priest/PriestActionFactory.h"
#include "../strategy/mage/MageActionFactory.h"
#include "../strategy/warlock/WarlockActionFactory.h"
#include "../strategy/warrior/WarriorActionFactory.h"
#include "../strategy/shaman/ShamanActionFactory.h"
#include "../strategy/paladin/PaladinActionFactory.h"
#include "../strategy/druid/DruidActionFactory.h"
#include "../strategy/hunter/HunterActionFactory.h"
#include "../strategy/rogue/RogueActionFactory.h"


ActionFactory* AiFactory::createActionFactory(Player* player, AiManagerRegistry* const aiRegistry)
{
    switch (player->getClass())
    {
    case CLASS_PRIEST:
        return new PriestActionFactory(aiRegistry);
        break;
    case CLASS_MAGE:
        return new MageActionFactory(aiRegistry);
        break;
    case CLASS_WARLOCK:
        return new WarlockActionFactory(aiRegistry);
        break;
    case CLASS_WARRIOR:
        return new WarriorActionFactory(aiRegistry);
        break;
    case CLASS_SHAMAN:
        return new ShamanActionFactory(aiRegistry);
        break;
    case CLASS_PALADIN:
        return new PaladinActionFactory(aiRegistry);
        break;
    case CLASS_DRUID:
        return new DruidActionFactory(aiRegistry);
        break;
    case CLASS_HUNTER:
        return new HunterActionFactory(aiRegistry);
        break;
    case CLASS_ROGUE:
        return new RogueActionFactory(aiRegistry);
        break;
    }
    return NULL;
}

Engine* AiFactory::createCombatEngine(Player* player, AiManagerRegistry* const facade, ActionFactory* actionFactory) {
	Engine* engine = NULL;

    engine = new Engine(facade, actionFactory);
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

Engine* AiFactory::createNonCombatEngine(Player* player, AiManagerRegistry* const facade, ActionFactory* actionFactory) {
	Engine* nonCombatEngine = NULL;
    nonCombatEngine = new Engine(facade, actionFactory);
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
    nonCombatEngine->addStrategies("nc", "emote", "food", "stay", "chat", NULL);
	return nonCombatEngine;
}