#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidAiObjectContext.h"

using namespace ai;


class CasterDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( CasterDruidTestCase );
    CPPUNIT_TEST( combat);
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
	CPPUNIT_TEST( curePoison );
	CPPUNIT_TEST( resurrect );
    CPPUNIT_TEST( cc );
	CPPUNIT_TEST( aoe );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidAiObjectContext(ai), "caster", NULL);

		addAura("moonkin form");
    }

protected:
    void combat()
    {
		removeAura("moonkin form");
		tick();
		addAura("moonkin form");

		tickInSpellRange();
		addTargetAura("faerie fire");

		tick();
		addTargetAura("insect swarm");

		tick();
		addTargetAura("moonfire");

        tick();
		tick();

		spellAvailable("starfire");
		tickInSpellRange();

        tickWithBalancePercent(49);

		assertActions(">S:moonkin form>T:faerie fire>T:insect swarm>T:moonfire>T:starfire>T:wrath>T:starfire>S:nature's grasp");
    }

	void healHimself()
    {
		tickInSpellRange();

		tickWithLowHealth(59);
		tickWithLowHealth(59);
		tickWithLowHealth(59);

		tick();
		addAura("moonkin form");

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

        assertActions(">T:faerie fire>S:caster form>S:regrowth>S:healing touch>S:moonkin form>T:insect swarm>S:caster form>S:healing touch>S:rejuvenation>S:regrowth>S:healing touch");
    }

	void healOthers()
    {
        tick();
        addAura("moonkin form");

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
        addAura("moonkin form");
        tickWithPartyLowHealth(1);
        tickWithPartyLowHealth(1);
        tickWithPartyLowHealth(1);

        assertActions(">T:faerie fire>S:caster form>P:regrowth on party>P:healing touch on party>S:caster form>P:healing touch on party>S:caster form>P:rejuvenation on party>P:regrowth on party");
    }

	void curePoison()
	{
		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("abolish poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("cure poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		assertActions(">S:abolish poison>P:abolish poison on party>S:cure poison>P:cure poison on party");
	}

	void resurrect()
	{
		tickWithDeadPartyMember();
		tickWithDeadPartyMember();

		assertActions(">S:caster form>P:rebirth");
	}

    void cc()
    {
        tickWithCcTarget("entangling roots");

        assertActions(">Cc:entangling roots on cc");
    }

    void aoe()
    {
        tickWithAttackerCount(4);
        tickWithAttackerCount(4);

		assertActions(">T:starfall>T:hurricane");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( CasterDruidTestCase );
