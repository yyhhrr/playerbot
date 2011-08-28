#include "pch.h"
#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidAiObjectContext.h"

using namespace ai;

class BearTankDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( BearTankDruidTestCase );
        CPPUNIT_TEST( druidMustDoMauls );
        CPPUNIT_TEST( combatVsMelee );
        CPPUNIT_TEST( druidMustHoldAggro );
        CPPUNIT_TEST( druidMustDemoralizeAttackers );
        CPPUNIT_TEST( bearFormIfDireNotAvailable );
        CPPUNIT_TEST( healHimself );
        CPPUNIT_TEST( intensiveHealing );
        CPPUNIT_TEST( healOthers );
        CPPUNIT_TEST( curePoison );
        CPPUNIT_TEST( interruptSpells );
        CPPUNIT_TEST( buff );
        CPPUNIT_TEST( cc );
        CPPUNIT_TEST( aoe );
        CPPUNIT_TEST( incompatibles );
    CPPUNIT_TEST_SUITE_END();


public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidAiObjectContext(ai), "bear", NULL);

		addAura("thorns");
        addTargetAura("faerie fire (feral)");
    }

protected:
    void bearFormIfDireNotAvailable()
    {
		tickWithSpellUnavailable("dire bear form");

		assertActions(">S:bear form");
    }

    void druidMustDemoralizeAttackers()
    {
        tick();

		spellAvailable("dire bear form");
		removeAura("dire bear form");

		tickWithAttackerCount(3);
		addAura("dire bear form");
		tickWithAttackerCount(3);

		tickInMeleeRange();

		tick();

		assertActions(">S:dire bear form>S:dire bear form>T:reach melee>T:swipe (bear)>T:demoralizing roar");
    }

    void druidMustHoldAggro()
    {
        tick();
        addAura("dire bear form");

		tickWithNoAggro();

        tick();
        tick();
        tick();

		assertActions(">S:dire bear form>T:growl>T:feral charge - bear>T:melee>T:lacerate");
    }

    void druidMustDoMauls()
    {
        tick();
        addAura("dire bear form");

		tickInMeleeRange();
		tick();

		tickWithRage(21);
		tickWithRage(21);
		tickWithRage(21);

		tickWithSpellAvailable("maul");

		assertActions(">S:dire bear form>T:melee>T:lacerate>T:melee>T:mangle (bear)>T:melee>T:maul");
    }

    void combatVsMelee()
    {
        removeTargetAura("faerie fire (feral)");

        tick();
        addAura("dire bear form");

        tick();
        tickInMeleeRange();

		tickOutOfMeleeRange();
		tick();
		tick();

		tickWithRage(41);
		tickWithRage(61);
        tickWithRage(61);
        tickWithRage(61);

        assertActions(">S:dire bear form>T:feral charge - bear>T:faerie fire (feral)>T:reach melee>T:melee>T:lacerate>T:melee>T:mangle (bear)>T:melee>T:maul");
    }

    void healHimself()
    {
        tick();
        addAura("dire bear form");

		tickInMeleeRange();
		tick();

		tickWithLowHealth(59);
		tickWithLowHealth(59);

        tick();
		addAura("bear form");
        tick();

		tickWithLowHealth(39);
		tickWithLowHealth(39);

        addAura("bear form");
        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);
        tickWithLowHealth(1);

        assertActions(">S:dire bear form>T:melee>T:lacerate>S:caster form>S:regrowth>S:bear form>T:melee>S:caster form>S:healing touch>S:survival instincts>S:barskin>S:caster form>S:rejuvenation>S:regrowth>S:healing touch");
    }

    void intensiveHealing()
    {
        addAura("dire bear form");
		tickWithLowHealth(1);

		assertActions(">S:survival instincts");
    }

    void healOthers()
    {
        tick();
        addAura("dire bear form");
        
        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
        addAura("dire bear form");
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);
        
        spellAvailable("healing touch");
        spellAvailable("regrowth");
        spellAvailable("rejuvenation");
        addAura("dire bear form");
        tickWithPartyLowHealth(1);
        tickWithPartyLowHealth(1);
        tickWithPartyLowHealth(1);

		assertActions(">S:dire bear form>S:caster form>P:healing touch on party>S:caster form>P:rejuvenation on party>P:regrowth on party");
    }
    void curePoison()
    {
        tick();
        addAura("dire bear form");

		tickWithAuraToDispel(DISPEL_POISON);
		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("abolish poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("cure poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		assertActions(">S:dire bear form>S:caster form>S:abolish poison>P:abolish poison on party>S:cure poison>P:cure poison on party");
    }
    void interruptSpells()
    {
        tick();
        addAura("dire bear form");

		tickInMeleeRange();
		tick();

		tickWithTargetIsCastingNonMeleeSpell();

        assertActions(">S:dire bear form>T:melee>T:lacerate>T:bash");
    }
	void buff()
	{
        removeAura("thorns");
        tick();

        removeTargetAura("faerie fire (feral)");
        tickInMeleeRange();
		addAura("dire bear form");

        tick();

        assertActions(">S:thorns>S:dire bear form>T:faerie fire (feral)");
	}

    void cc()
    {
        addAura("dire bear form");
        tickWithCcTarget("entangling roots");
        tickWithCcTarget("entangling roots");

        assertActions(">S:caster form>Cc:entangling roots on cc");
    }

    void aoe()
    {
        addAura("dire bear form");
		tickInMeleeRange();
		tick();
		tickWithAttackerCount(3);

		assertActions(">T:melee>T:lacerate>T:swipe (bear)");
    }

    void incompatibles()
    {
        engine->addStrategies("bear", "cat", "caster", "dps", "tank", NULL);

        CPPUNIT_ASSERT(engine->ListStrategies() == "Strategies: bear");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( BearTankDruidTestCase );
