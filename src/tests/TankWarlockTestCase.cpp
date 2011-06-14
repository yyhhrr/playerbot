#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warlock/WarlockAiObjectContext.h"

using namespace ai;


class TankWarlockTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( TankWarlockTestCase );
      CPPUNIT_TEST( summonPet );
      CPPUNIT_TEST( cc );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarlockAiObjectContext(ai), "tank", NULL);
    }

protected:

    void summonPet()
    {
        itemAvailable("soul shard", 2);
        tickWithNoPet();

		assertActions(">S:summon voidwalker");
    }

    void cc()
    {
        tickWithCcTarget("banish");

        assertActions(">Cc:banish");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarlockTestCase );
