#pragma once

#include "string"

using namespace std;
using namespace ai;

namespace ai
{
    class MockAiSpellManager : public AiSpellManager
    {
    public:
        MockAiSpellManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry, string *buffer) : AiSpellManager(ai, aiRegistry) 
        { 
        }

	public:
    };

}