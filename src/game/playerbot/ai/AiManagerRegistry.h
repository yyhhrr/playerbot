#pragma once

using namespace std;

#define MAX_AI_MANAGER_TYPE 2

class Player;
class PlayerbotAI;

namespace ai 
{
    class AiManagerBase;
    
	class AiSpellManager;
	class AiInventoryManager;
	class AiManagerBase;

	enum AiManagerType
	{
		AiSpellManagerType = 0,
		AiInventoryManagerType = 1
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
		AiInventoryManager* GetInventoryManager() { return (AiInventoryManager*)managers[AiInventoryManagerType]; }

		int GetManagerCount() { return MAX_AI_MANAGER_TYPE; }
		AiManagerBase** GetManagers() { return managers; }
        PlayerbotAI* GetAi() { return ai; }

	protected:
		AiManagerBase* managers[MAX_AI_MANAGER_TYPE];
        PlayerbotAI* ai;
	};

};