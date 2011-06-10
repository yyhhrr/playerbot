#pragma once

class ai::AiManagerRegistry;
class Player;

using namespace ai;

class AiFactory
{
public:
    static ActionFactory* createActionFactory(Player* player, AiManagerRegistry* const aiRegistry);
	static Engine* createCombatEngine(Player* player, AiManagerRegistry* const facade, ActionFactory* actionFactory);
	static Engine* createNonCombatEngine(Player* player, AiManagerRegistry* const facade, ActionFactory* actionFactory);
};
