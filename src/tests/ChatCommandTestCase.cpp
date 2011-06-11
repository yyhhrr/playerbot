#include "pch.h"

#include "aitest.h"
#include "MockAiObjectContext.h"
#include "MockedAiObjectContextTestCase.h"
#include "../game/playerbot/strategy/ChatCommandHandlerStrategy.h"

using namespace ai;


class ChatCommandTestCase : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( ChatCommandTestCase );
  CPPUNIT_TEST( stats );
  CPPUNIT_TEST( leave );
  CPPUNIT_TEST( quests );
  CPPUNIT_TEST( reputation );
  CPPUNIT_TEST( log );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "chat", NULL);
    }

protected:
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

    void log()
    {
        assertCommand("log");
        assertParametrizedCommand("log", "debug");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ChatCommandTestCase );
