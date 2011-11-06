#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/mage/MageAiObjectContext.h"

using namespace ai;


class MageNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( MageNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( low_mana );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new MageAiObjectContext(ai), "nc", NULL);
		set<uint8>("item count", "food", 1);
		set<uint8>("item count", "drink", 1);
    }

protected:
    void buff()
    {
		tick();
        addAura("arcane intellect");

		tickWithSpellAvailable("arcane intellect");
        addPartyAura("arcane intellect");

        tick();
        tick();
        tick();
        addAura("mage armor");

		tickWithNoDrink();
		tickWithNoFood();

        assertActions(">S:arcane intellect>P:arcane intellect on party>S:mage armor>S:ice armor>S:frost armor>S:conjure water>S:conjure food");
    }
    
    void low_mana()
    {
        addAura("arcane intellect");
        addPartyAura("arcane intellect");
        addAura("mage armor");

        tickWithLowMana(5);
        tickWithLowMana(5);

        set<uint8>("item count", "drink", 0);
        tickWithLowMana(5);

        assertActions(">S:evocation>S:drink>S:flee");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( MageNonCombatTestCase );
