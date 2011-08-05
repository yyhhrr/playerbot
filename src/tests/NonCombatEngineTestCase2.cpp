#include "pch.h"
#include "aitest.h"

#include "EngineTestBase.h"
#include "MockedAiObjectContextTestCase.h"

using namespace ai;


class NonCombatEngineTestCase2 : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( NonCombatEngineTestCase2 );
      CPPUNIT_TEST( emote );
      CPPUNIT_TEST( followMasterRandom );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
		EngineTestBase::setUp();
        setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "emote", NULL);
	}

protected:
    void emote()
    {
        tickWithTrigger("random");
        tickWithTrigger("seldom");

        assertActions(">S:emote>S:suggest what to do");
    }

    void followMasterRandom()
    {
        engine->removeStrategy("emote");
        engine->addStrategy("be near");

        tickWithTrigger("random");
        tickWithTrigger("target in sight");

        assertActions(">S:move random>S:stay combat");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase2 );
