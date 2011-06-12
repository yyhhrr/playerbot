#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiTargetManager : public AiTargetManager
    {
    public:
		MockAiTargetManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : 
		  AiTargetManager(ai, aiRegistry) 
		  {
          }

	public:

	public:
		static MockAiTargetManager* Instance();

	public:
    };

}