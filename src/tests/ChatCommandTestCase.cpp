#include "pch.h"

#include "aitest.h"
#include "MockAiObjectContext.h"
#include "../game/playerbot/strategy/ChatCommandHandlerStrategy.h"

using namespace ai;


class ChatCommandTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( ChatCommandTestCase );
  CPPUNIT_TEST( stats );
  CPPUNIT_TEST( leave );
  CPPUNIT_TEST( quests );
  CPPUNIT_TEST( reputation );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockAiObjectContext* context;

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "chat", NULL);
    }

protected:
    void assertCommand(const char* trigger)
    {
        assertCommand(trigger, trigger);
    }

    void assertCommand(const char* trigger, const char* expectedAction)
    {
        ai->buffer.clear();

        context->GetTrigger(trigger)->ExternalEvent("");
        tick();

        assertActions((string(">") + expectedAction).c_str());
    }

    void assertParametrizedCommand(const char* trigger, const char* param)
    {
        ai->buffer.clear();

        context->GetTrigger(trigger)->ExternalEvent(param);
        tick();

        assertActions((string(">") + trigger + "(" + param + ")").c_str());
    }

 	void stats()
	{
        assertCommand("stats");
	}

    void leave()
    {
        assertCommand("leave");
    }

    void reputation()
    {
        assertCommand("rep", "reputation");
        assertCommand("reputation");
    }

    void quests()
    {
        assertCommand("quests");
        assertParametrizedCommand("quests", "summary");
        assertParametrizedCommand("quests", "completed");
        assertParametrizedCommand("quests", "incompleted");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ChatCommandTestCase );
