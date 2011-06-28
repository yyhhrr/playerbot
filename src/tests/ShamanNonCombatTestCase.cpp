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
	    tickWhileSwimming();

		assertActions(">S:water breathing>S:water walking");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ShamanNonCombatTestCase );
