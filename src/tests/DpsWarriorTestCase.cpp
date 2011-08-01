#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warrior/WarriorAiObjectContext.h"

using namespace ai;


class DpsWarriorTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DpsWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( execute );
    CPPUNIT_TEST( hamstring );
	CPPUNIT_TEST( victoryRush );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarriorAiObjectContext(ai), "dps", NULL);

		spellUnavailable("revenge");
        addAura("battle shout");
        set<uint8>("rage", "self target", 20);
    }

protected:
    void buff()
    {
        removeAura("battle shout");

        tickInSpellRange(); // reach melee
		tickInMeleeRange();
        tick();

		assertActions(">S:battle shout>S:battle stance>T:charge");

    }

    void warriorMustDemoralizeAttackers()
    {
        tickInMeleeRange(); // melee

		tickWithAttackerCount(3);

		assertActions(">S:battle stance>T:demoralizing shout");
    }

    void warriorMustHoldAggro()
    {
        tickInMeleeRange(); // melee

		tickWithNoAggro();
		tickWithNoAggro();

        tick();

		assertActions(">S:battle stance>T:mocking blow>T:charge>T:melee");
    }

    void combatVsMelee()
    {
		tickInSpellRange();
		tickInSpellRange();

		tickInMeleeRange();

		tickInSpellRange();

		tickInMeleeRange();

        tick();

		spellAvailable("rend");
        addTargetAura("rend");

        tickWithRage(41);
        tickWithRage(41);

        tick(); // bloodrage

		assertActions(">S:battle stance>T:charge>T:melee>T:reach melee>T:rend>T:melee>T:bloodthirst>T:heroic strike>S:bloodrage");
    }

    void boost()
    {
        tickInMeleeRange(); // battle stance

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);
		tickWithBalancePercent(1);

        tick(); // melee

		assertActions(">S:battle stance>S:death wish>S:berserker rage>T:charge>T:melee");
    }

    void execute()
    {
        tickInMeleeRange(); // battle stance

		tickWithTargetLowHealth(19);

        tick(); // melee

		assertActions(">S:battle stance>T:execute>T:charge");
    }


    void hamstring ()
    {
		tickInMeleeRange(); // reach melee

		tickWithTargetIsMoving();
		tickWithTargetIsMoving();

        tickWithSpellAvailable("defensive stance"); // melee

		assertActions(">S:battle stance>T:hamstring>T:charge>T:melee");
    }


	void victoryRush()
	{
		tickInMeleeRange();
		addAura("victory rush");

		tick();

		assertActions(">S:battle stance>T:victory rush");
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsWarriorTestCase );
