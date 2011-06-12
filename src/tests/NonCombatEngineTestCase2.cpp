#include "pch.h"
#include "aitest.h"

#include "EngineTestBase.h"
#include "MockedAiObjectContextTestCase.h"

using namespace ai;


class NonCombatEngineTestCase2 : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( NonCombatEngineTestCase2 );
  CPPUNIT_TEST( emote );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
		EngineTestBase::setUp();
        setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "nc", NULL);
	}

protected:
    void emote()
    {
        engine->addStrategy("emote");

        trigger("random");
        tick();

        CPPUNIT_ASSERT(strstr(ai->buffer.c_str(), ">S:emote"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase2 );
