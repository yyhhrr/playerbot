#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiMoveManager : public AiMoveManager
    {
    public:
        MockAiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry, string *buffer) : AiMoveManager(ai, aiRegistry) 
        {
			this->buffer = buffer;
		}

	public:
		virtual void Attack(Unit* target);

	private:
		string *buffer;

    };

}