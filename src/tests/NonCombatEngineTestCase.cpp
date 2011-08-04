#include "pch.h"
#include "aitest.h"

#include "EngineTestBase.h"

using namespace ai;


class NonCombatEngineTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( NonCombatEngineTestCase );
      CPPUNIT_TEST( followMasterRandom );
      CPPUNIT_TEST( followMaster );
      CPPUNIT_TEST( followLine );
      CPPUNIT_TEST( stay );
      CPPUNIT_TEST( eatDrink );
      CPPUNIT_TEST( dpsAssist );
      CPPUNIT_TEST( tankAssist );
      CPPUNIT_TEST( loot );
      CPPUNIT_TEST( gather );
      CPPUNIT_TEST( goaway );
      CPPUNIT_TEST( passive );
      CPPUNIT_TEST( movementStrategies );
      CPPUNIT_TEST( assistStrategies );
      CPPUNIT_TEST( out_of_react );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new AiObjectContext(ai), NULL);
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

    void followMasterRandom()
    {
        engine->addStrategy("be near");

        set<float>("distance", "master target", 20);
        tick();

        assertActions(">S:be near");
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

        set<float>("distance", "loot target", 15.0f);
        tick();

        set<float>("distance", "loot target", 0.0f);
        set<bool>("can loot", true);
        tick();

        set<bool>("can loot", false);
        tick();

        assertActions(">S:loot>S:move to loot>S:open loot>S:stay");
    }

    void gather()
    {
		engine->addStrategy("stay");
		engine->addStrategy("gather");
		engine->addStrategy("loot");

		set<list<ObjectGuid>>("possible targets", list<ObjectGuid>());
		tick();

        tickWithLootAvailable();

        set<bool>("can loot", true);
        tick();

        assertActions(">S:add gathering loot>S:loot>S:open loot");
    }

    void eatDrink()
    {
        engine->addStrategy("food");
        set<uint8>("item count", "food", 1);
        set<uint8>("item count", "drink", 1);

		tickWithLowHealth(1);
		tickWithLowMana(1);

        assertActions(">S:food>S:drink");
    }

    void passive()
    {
        engine->addStrategy("stay");
        engine->addStrategy("passive");

        tick();
		tickWithNoTarget();

        assertActions(">S:stay>S:stay");
    }

    void movementStrategies()
    {
        engine->addStrategy("follow master");
        engine->addStrategy("follow line");
        engine->addStrategy("be near");
        engine->addStrategy("goaway");
        engine->addStrategy("stay");

        cout << engine->ListStrategies();
        CPPUNIT_ASSERT(engine->ListStrategies() == "Strategies: stay");
    }

    void assistStrategies()
    {
        engine->addStrategy("dps assist");
        engine->addStrategy("tank asssist");
        engine->addStrategy("dps aoe");
        engine->addStrategy("tank asssist");
        engine->addStrategy("grind");

        cout << engine->ListStrategies();
        CPPUNIT_ASSERT(engine->ListStrategies() == "Strategies: grind");
    }

    void out_of_react()
    {
        engine->addStrategy("follow master");
        set<float>("distance", "master target", 100.0f / 2 + 10);
        tick();
        assertActions(">S:tell out of react range");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase );
