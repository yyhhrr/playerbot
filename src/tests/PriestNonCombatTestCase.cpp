#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/priest/PriestAiObjectContext.h"

using namespace ai;


class PriestNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( PriestNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( healing );
    CPPUNIT_TEST( nonCombat );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new PriestAiObjectContext(ai), "nc", NULL);

        addAura("power word: fortitude");
        addAura("divine spirit");
        addAura("inner fire");
        addPartyAura("power word: fortitude");
        addPartyAura("divine spirit");
    }

protected:
    void nonCombat()
    {
        addPartyAura("power word: fortitude");

		tickWithDeadPartyMember();

		assertActions(">P:resurrection");
    }

    void healing()
    {
        addPartyAura("power word: fortitude");

		tickWithLowHealth(30);
        spellAvailable("flash heal");
		tickWithPartyLowHealth(30);
		tickWithLowHealth(10);
		spellAvailable("greater heal");
		tickWithPartyLowHealth(10);

		assertActions(">S:flash heal>P:flash heal on party>S:greater heal>P:greater heal on party");
    }

    void buff()
    {
		removeAura("power word: fortitude");
        removeAura("divine spirit");
        removeAura("inner fire");
        removePartyAura("power word: fortitude");
        removePartyAura("divine spirit");

        tick();
        addAura("divine spirit");

        tick();
        addAura("power word: fortutude");

        tickWithSpellAvailable("divine spirit");
        addPartyAura("divine spirit");

        tick(); // inner fire

        tick();
        addAura("power word: fortitude");

        tickWithSpellAvailable("power word: fortitude");
        addPartyAura("power word: fortitude");

		assertActions(">S:divine spirit>S:power word: fortitude>P:divine spirit on party>S:inner fire>P:power word: fortitude on party");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( PriestNonCombatTestCase );
