#include "pch.h"
#include "aitest.h"

#include "EngineTestBase.h"

using namespace ai;


class NonCombatEngineTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( NonCombatEngineTestCase );
  CPPUNIT_TEST( followMaster );
  CPPUNIT_TEST( followLine );
  CPPUNIT_TEST( stay );
  CPPUNIT_TEST( eatDrink );
  CPPUNIT_TEST( dpsAssist );
  CPPUNIT_TEST( tankAssist );
  CPPUNIT_TEST( loot );
  CPPUNIT_TEST( goaway );
  CPPUNIT_TEST( passive );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new AiObjectContext(ai), "nc", NULL);
	}

protected:
    void goaway() 
    {
        engine->addStrategy("goaway");
		tickWithAttackerCount(0);
        assertActions(">S:goaway");
    }
    
    void followMaster()
    {
        engine->addStrategy("follow master");

		tickWithAttackerCount(0);
		assertActions(">S:follow master");
    }

	void followLine()
	{
		engine->addStrategy("follow line");

		tickWithAttackerCount(0);
		assertActions(">S:follow line");
	}

    void stay()
    {
		engine->addStrategy("stay");

		tickWithAttackerCount(0);
		assertActions(">S:stay");
    }

    void dpsAssist()
    {
        engine->addStrategy("stay");
        engine->addStrategy("dps assist");

		tick();
		tickWithNoTarget();

		assertActions(">S:stay>Dps:dps assist");
    }


	void tankAssist()
	{
		engine->addStrategy("stay");
		engine->addStrategy("tank assist");

		tick();
		tickWithNoTarget();

		assertActions(">S:stay>Tank:tank assist");
	}
	
    void loot()
    {
		engine->addStrategy("stay");
		engine->addStrategy("loot");

		tickWithLootAvailable();
		tick();

        assertActions(">S:loot>S:stay");
    }

    void eatDrink()
    {
        engine->addStrategy("food");

		tickWithLowHealth(1);
		tickWithLowMana(1);

        assertActions(">S:eat>S:drink");
    }

    void passive()
    {
        engine->addStrategy("stay");
        engine->addStrategy("passive");

        tick();
		tickWithNoTarget();

        assertActions(">S:stay>S:stay");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase );
