#include "pch.h"
#include "aitest.h"
#include "MockAiManagerRegistry.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

MockAiManagerRegistry::MockAiManagerRegistry() : AiManagerRegistry()
{
    ai = new MockPlayerbotAIBase();
	managers[AiSpellManagerType] = new MockAiSpellManager(ai, this, &buffer);
	managers[AiInventoryManagerType] = new MockAiInventoryManager(ai, this, &buffer);
	managers[AiSocialManagerType] = new MockAiSocialManager(ai, this, &buffer);
}

MockAiManagerRegistry::~MockAiManagerRegistry()
{
}
