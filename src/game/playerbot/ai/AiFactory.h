#pragma once

class ai::AiManagerRegistry;
class Player;

using namespace ai;

class AiFactory
{
public:
    static AiObjectContext* createAiObjectContext(Player* player, AiManagerRegistry* const aiRegistry);
	static Engine* createCombatEngine(Player* player, AiManagerRegistry* const facade, AiObjectContext* AiObjectContext);
	static Engine* createNonCombatEngine(Player* player, AiManagerRegistry* const facade, AiObjectContext* AiObjectContext);
};
