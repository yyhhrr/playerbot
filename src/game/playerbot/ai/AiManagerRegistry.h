#pragma once

using namespace std;

#define MAX_AI_MANAGER_TYPE 6

class Player;
class PlayerbotAI;

namespace ai 
{
    class AiManagerBase;
    
	class AiSpellManager;
	class AiTargetManager;
	class AiMoveManager;
	class AiInventoryManager;
	class AiSocialManager;
	class AiQuestManager;
	class AiStrategyManager;
	class AiManagerBase;

	enum AiManagerType
	{
		AiSpellManagerType = 0,
		AiTargetManagerType = 1,
		AiMoveManagerType = 2,
		AiInventoryManagerType = 3,
		AiSocialManagerType = 4,
		AiQuestManagerType = 5
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
		AiTargetManager* GetTargetManager() { return (AiTargetManager*)managers[AiTargetManagerType]; }
		AiMoveManager* GetMoveManager() { return (AiMoveManager*)managers[AiMoveManagerType]; }
		AiInventoryManager* GetInventoryManager() { return (AiInventoryManager*)managers[AiInventoryManagerType]; }
		AiSocialManager* GetSocialManager() { return (AiSocialManager*)managers[AiSocialManagerType]; }
		AiQuestManager* GetQuestManager() { return (AiQuestManager*)managers[AiQuestManagerType]; }

		int GetManagerCount() { return MAX_AI_MANAGER_TYPE; }
		AiManagerBase** GetManagers() { return managers; }
        PlayerbotAI* GetAi() { return ai; }

	protected:
		AiManagerBase* managers[MAX_AI_MANAGER_TYPE];
        PlayerbotAI* ai;
	};

};