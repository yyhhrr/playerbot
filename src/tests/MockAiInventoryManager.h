#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiInventoryManager : public AiInventoryManager
    {
    public:
        MockAiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry, string *buffer) : AiInventoryManager(ai, aiRegistry) 
        {
			this->buffer = buffer;
		}

	private:
		string *buffer;

    };

}