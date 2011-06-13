#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiManagers.h"


using namespace ai;
using namespace std;

AiManagerRegistry::AiManagerRegistry() : ai(NULL)
{
	for (int i=0; i<MAX_AI_MANAGER_TYPE; i++)
		managers[i] = NULL;
}

AiManagerRegistry::AiManagerRegistry(PlayerbotAI* ai) : ai(ai)
{
	for (int i=0; i<MAX_AI_MANAGER_TYPE; i++)
		managers[i] = NULL;

	managers[AiSpellManagerType] = new AiSpellManager(ai, this);
	managers[AiInventoryManagerType] = new AiInventoryManager(ai, this);
	managers[AiSocialManagerType] = new AiSocialManager(ai, this);
}

AiManagerRegistry::~AiManagerRegistry()
{
	for (int i=0; i<MAX_AI_MANAGER_TYPE; i++)
	{
		if (managers[i]) 
		{
			delete managers[i];
			managers[i] = NULL;
		}
	}
}
