#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/shaman/ShamanAiObjectContext.h"

using namespace ai;


class MeleeShamanTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( MeleeShamanTestCase );
    CPPUNIT_TEST( combat );
	CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new ShamanAiObjectContext(ai), "melee", NULL);

        addAura("lightning shield");
        addAura("windfury weapon");
    }

protected:
    void combat()
    {
		tick();
		tickInMeleeRange();
		tick();
		tick();
		tick();
        
		assertActions(">T:reach melee>T:melee>T:stormstrike>T:lava lash>T:melee");
    }

    void buff()
    {
        removeAura("lightning shield");

        tick(); 
        addAura("lightning shield");

        removeAura("windfury weapon");
        tick(); 
        tick(); 
        addAura("windfury weapon");

        assertActions(">S:lightning shield>S:windfury weapon>S:rockbiter weapon");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MeleeShamanTestCase );
