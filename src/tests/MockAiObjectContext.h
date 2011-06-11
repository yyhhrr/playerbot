#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiObjectContext : public AiObjectContext
    {
    public:
        MockAiObjectContext(AiManagerRegistry* const ai, AiObjectContext *realContext, string *buffer);
    
    public:
        virtual Strategy* GetStrategy(const char* name);
        virtual Trigger* GetTrigger(const char* name);
        virtual Action* GetAction(const char* name);

	private:
		string *buffer;
        AiObjectContext *realContext;
        map<string, Trigger*> triggers;
        map<string, Action*> actions;
    };

}