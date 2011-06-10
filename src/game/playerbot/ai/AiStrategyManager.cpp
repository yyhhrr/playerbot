#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiStrategyManager.h"
#include "../strategy/Engine.h"
#include "AiFactory.h"

using namespace std;
using namespace ai;

AiStrategyManager::AiStrategyManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : 
	AiManagerBase(ai, aiRegistry)
{
    if (!aiRegistry)
        return;

	combatEngine = AiFactory::createCombatEngine(bot, aiRegistry, ai->GetActionFactory());
	nonCombatEngine = AiFactory::createNonCombatEngine(bot, aiRegistry, ai->GetActionFactory());

	currentEngine = nonCombatEngine;
}

AiStrategyManager::~AiStrategyManager() 
{
	currentEngine = NULL;

    if (combatEngine) 
	{
        delete combatEngine;
        combatEngine = NULL;
    }
    if (nonCombatEngine) 
	{
        delete nonCombatEngine;
        nonCombatEngine = NULL;
    }
}


void AiStrategyManager::HandleCommand(const string& text, Player& fromPlayer)
{

}

void AiStrategyManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
}

