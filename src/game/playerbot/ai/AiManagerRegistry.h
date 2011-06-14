#pragma once

using namespace std;

#define MAX_AI_MANAGER_TYPE 1

class Player;
class PlayerbotAI;

namespace ai 
{
    class AiManagerBase;
    
	class AiSpellManager;
	class AiManagerBase;

	enum AiManagerType
	{
		AiSpellManagerType = 0
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

		int GetManagerCount() { return MAX_AI_MANAGER_TYPE; }
		AiManagerBase** GetManagers() { return managers; }
        PlayerbotAI* GetAi() { return ai; }

	protected:
		AiManagerBase* managers[MAX_AI_MANAGER_TYPE];
        PlayerbotAI* ai;
	};

};