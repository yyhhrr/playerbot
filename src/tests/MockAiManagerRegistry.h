#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
	class MockPlayerbotAIBase : public PlayerbotAI
	{
	public:
		MockPlayerbotAIBase() : PlayerbotAI() {}
        void SetContext(AiObjectContext* context) { this->aiObjectContext = context; }
	};

    class MockAiManagerRegistry : public AiManagerRegistry
    {
    public:
		MockAiManagerRegistry();
		virtual ~MockAiManagerRegistry();

    public:
        void SetContext(AiObjectContext* context) { ((MockPlayerbotAIBase*)ai)->SetContext(context); }

	public:
		std::string buffer;
	};

}