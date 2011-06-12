#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/paladin/PaladinAiObjectContext.h"

using namespace ai;


class PaladinNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( PaladinNonCombatTestCase );
        CPPUNIT_TEST( buff );
		CPPUNIT_TEST( resurrect );
    CPPUNIT_TEST_SUITE_END();


public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new PaladinAiObjectContext(ai), "nc", NULL);

        set<uint8>("attacker count", 0);
    }

protected:
    void buff()
    {
        tick(); 
        set<bool>("mounted", true);
		tick();
        set<bool>("mounted", false);

		assertActions(">P:blessing of kings on party>S:crusader aura");
    }

	void resurrect()
	{
		tickWithDeadPartyMember();
		assertActions(">P:redemption");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( PaladinNonCombatTestCase );
