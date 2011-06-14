#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warlock/WarlockAiObjectContext.h"

using namespace ai;


class DpsWarlockTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( DpsWarlockTestCase );
      CPPUNIT_TEST( combatVsMelee );
      CPPUNIT_TEST( summonPet );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarlockAiObjectContext(ai), "dps", NULL);
    }

protected:
 	void combatVsMelee()
	{
        tick(); 
        addAura("corruption");
        tick(); 
        addAura("curse of agony");
        
        tickWithLowHealth(49);

        tick(); 

		tickWithTargetLowHealth(19);

        set<uint8>("item count", "soul shard", 2);
		spellAvailable("drain soul");
		tick();

		addAura("shadow trance"); 
		tick();

		assertActions(">T:corruption>T:curse of agony>T:drain life>T:shoot>T:drain soul>T:shadow bolt");
	}

    void summonPet()
    {
        tickWithNoPet();

		assertActions(">S:summon imp");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsWarlockTestCase );
