#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidAiObjectContext.h"

using namespace ai;


class CatDpsDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( CatDpsDruidTestCase );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( intensiveHealing );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( cower );
    CPPUNIT_TEST( buff );
	CPPUNIT_TEST( aoe );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidAiObjectContext(ai), "cat", NULL);

		addAura("cat form");
        addAura("thorns");
		addTargetAura("faerie fire (feral)");
    }

protected:

    void combatVsMelee()
    {
		tickInMeleeRange();

		tick();

        tickWithComboPoints(5);
        tickWithComboPoints(5);

		assertActions(">T:rake>T:mangle (cat)>T:ferocious bite>T:rip");
    }

	void healHimself()
	{
		tickInMeleeRange();

		tickWithLowHealth(59);
		tickWithLowHealth(59);
		tickWithLowHealth(59);

		tick();
		addAura("cat form");
		tick();

        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
		tickWithLowHealth(39);
		tickWithLowHealth(39);

        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);

        assertActions(">T:rake>S:caster form>S:regrowth>S:healing touch>S:cat form>T:mangle (cat)>S:caster form>S:healing touch>S:survival instincts>S:barskin>S:rejuvenation>S:regrowth>S:healing touch");
	}

    void intensiveHealing()
    {
		tickWithLowHealth(1);

		assertActions(">S:survival instincts");
    }

    void healOthers()
    {
        tickInMeleeRange();
        addAura("cat form");

        tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(59);

        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
        addAura("dire bear form");
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);

        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
        addAura("cat form");
        tickWithPartyLowHealth(1);
        tickWithPartyLowHealth(1);
        tickWithPartyLowHealth(1);

        assertActions(">T:rake>S:caster form>P:regrowth on party>P:healing touch on party>S:caster form>P:healing touch on party>S:caster form>P:rejuvenation on party>P:regrowth on party");
    }

    void boost()
    {
		tickWithBalancePercent(49);
		tick();

		assertActions(">S:tiger's fury>T:reach melee");
    }

    void cower()
    {
		tickWithMyAttackerCount(2);

		tickOutOfMeleeRange();
		assertActions(">S:cower>T:reach melee");
    }

    void buff()
    {
        removeAura("cat form");
        removeAura("thorns");
        tick();

        removeTargetAura("faerie fire (feral)");
        tickInMeleeRange();

        assertActions(">S:cat form>T:faerie fire (feral)");
    }

    void aoe()
    {
		tickInMeleeRange();
		tickWithAttackerCount(3);

		assertActions(">T:rake>T:swipe (cat)");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( CatDpsDruidTestCase );
