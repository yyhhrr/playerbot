#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/hunter/HunterAiObjectContext.h"

using namespace ai;

class DpsHunterEngineTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( DpsHunterEngineTestCase );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST( summonPet );
  CPPUNIT_TEST( lowMana );
  CPPUNIT_TEST( boost );
  CPPUNIT_TEST( cc );
  CPPUNIT_TEST( aoe );
  CPPUNIT_TEST( buff );
  CPPUNIT_TEST( incompatibles );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new HunterAiObjectContext(ai), "dps", NULL);
		engine->addStrategy("bdps");

        addAura("aspect of the hawk");
    }

protected:
 	void combatVsMelee()
	{
        removeAura("aspect of the hawk");

		tick();
        addAura("aspect of the hawk");

		tick();
        tick();
		tick();
		addTargetAura("serpent sting");

		tick();
		tick();

		tickInMeleeRange();
		tickInSpellRange();

		// resetSpells
		tickWithSpellUnavailable("aimed shot");

        tick();
		tickWithSpellAvailable("auto shot");

		assertActions(">S:aspect of the hawk>T:hunter's mark>T:black arrow>T:serpent sting>T:explosive shot>T:auto shot>S:flee>T:concussive shot>T:wyvern sting>T:arcane shot>T:auto shot");

	}

    void lowMana()
    {
        spellUnavailable("serpent sting");
        spellUnavailable("concussive shot");
        removeAura("aspect of the hawk");

		tickWithLowMana(30);
		tickWithLowMana(30);

		tick();

		assertActions(">S:aspect of the viper>T:viper sting>S:aspect of the hawk");

    }

    void summonPet()
    {
        tickWithNoPet();

		tickWithPetDead();
		tickWithPetLowHealth(30);

		assertActions(">S:call pet>S:revive pet>Pet:mend pet");
	}


    void boost()
    {
		tick();
        spellUnavailable("serpent sting");

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);

		assertActions(">T:hunter's mark>S:rapid fire>S:readyness");
    }


    void cc()
    {
        tickWithCcTarget("freezing trap");

        assertActions(">Cc:freezing trap");
    }

    void aoe()
    {
		addTargetAura("hunter's mark");
		addTargetAura("black arrow");
		addTargetAura("serpent sting");
        tickWithAttackerCount(3);
		tickWithAttackerCount(4);

		assertActions(">T:multi-shot>T:volley");
    }

	void buff()
	{
		engine->removeStrategy("bdps");
		engine->addStrategy("rnature");
		removeAura("aspect of the hawk");

		tick();
		addAura("aspect of the wild");

		assertActions(">S:aspect of the wild");

	}

    void incompatibles()
    {
        engine->removeStrategy("dps");
        engine->addStrategies("bdps", "bspeed", "rnature", NULL);

        CPPUNIT_ASSERT(engine->ListStrategies() == "Strategies: rnature");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsHunterEngineTestCase );
