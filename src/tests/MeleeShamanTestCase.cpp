#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/shaman/ShamanAiObjectContext.h"

using namespace ai;


class MeleeShamanTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( MeleeShamanTestCase );
    CPPUNIT_TEST( combat );
	CPPUNIT_TEST( buff );
	CPPUNIT_TEST( incompatibles );
    CPPUNIT_TEST( aoe );
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
		tickInMeleeRange();
        tick();
		tick();
		tick();

        assertActions(">S:searing totem>T:stormstrike>T:lava lash>T:melee");
    }

    void buff()
    {
        removeAura("lightning shield");
        tickInMeleeRange();

        tick();
        addAura("lightning shield");

        removeAura("windfury weapon");
        tick();
        tick();
        addAura("windfury weapon");

        assertActions(">S:lightning shield>S:searing totem>S:windfury weapon>S:rockbiter weapon");
    }

    void incompatibles()
    {
        engine->addStrategies("melee", "dps", "heal", NULL);

        CPPUNIT_ASSERT(engine->ListStrategies() == "Strategies: heal");
    }

    void aoe()
    {
        engine->addStrategy("melee aoe");

        tickInMeleeRange();
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);

        assertActions(">S:searing totem>S:magma totem>T:fire nova");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MeleeShamanTestCase );
