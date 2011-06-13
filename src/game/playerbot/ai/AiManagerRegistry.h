#pragma once

using namespace std;

#define MAX_AI_MANAGER_TYPE 4

class Player;
class PlayerbotAI;

namespace ai 
{
    class AiManagerBase;
    
	class AiSpellManager;
	class AiMoveManager;
	class AiInventoryManager;
	class AiSocialManager;
	class AiStrategyManager;
	class AiManagerBase;

	enum AiManagerType
	{
		AiSpellManagerType = 0,
		AiMoveManagerType = 1,
		AiInventoryManagerType = 2,
		AiSocialManagerType = 3
	};

	class AiManagerRegistry
	{
	public:
		// for testing only
		AiManagerRegistry();
		AiManagerRegistry(PlayerbotAI* ai);
		virtual ~AiManagerRegistry();

	public:
		AiSpellManager* GetSpellManager() { return (AiSpellManager*)managers[AiSpellManagerType]; }
		AiMoveManager* GetMoveManager() { return (AiMoveManager*)managers[AiMoveManagerType]; }
		AiInventoryManager* GetInventoryManager() { return (AiInventoryManager*)managers[AiInventoryManagerType]; }
		AiSocialManager* GetSocialManager() { return (AiSocialManager*)managers[AiSocialManagerType]; }

		int GetManagerCount() { return MAX_AI_MANAGER_TYPE; }
		AiManagerBase** GetManagers() { return managers; }
        PlayerbotAI* GetAi() { return ai; }

	protected:
		AiManagerBase* managers[MAX_AI_MANAGER_TYPE];
        PlayerbotAI* ai;
	};

};