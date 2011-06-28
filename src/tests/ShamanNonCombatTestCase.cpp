#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/shaman/ShamanAiObjectContext.h"

using namespace ai;


class ShamanNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( ShamanNonCombatTestCase );
	CPPUNIT_TEST( ressurect );
	CPPUNIT_TEST( swimming );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new ShamanAiObjectContext(ai), "nc", NULL);
    }

protected:
	void ressurect()
	{
		tickWithDeadPartyMember();

		assertActions(">P:ancestral spirit");
	}

	void swimming()
	{
	    tickWhileSwimming();
	    addAura("water breathing");

	    tickWhileSwimming();
        addAura("water walking");

        spellAvailable("water breathing");
        tickWhileSwimming();
        addPartyAura("water breathing");

        spellAvailable("water walking");
        tickWhileSwimming();
        addPartyAura("water walking");

		assertActions(">S:water breathing>S:water walking>P:water breathing on party>P:water walking on party");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ShamanNonCombatTestCase );
