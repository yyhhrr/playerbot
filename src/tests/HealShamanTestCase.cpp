#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/shaman/ShamanAiObjectContext.h"

using namespace ai;


class HealShamanTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( HealShamanTestCase );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( interruptSpell );
	CPPUNIT_TEST( dispel );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new ShamanAiObjectContext(ai), "heal", NULL);

        addAura("water shield");
        addAura("earthliving weapon");
    }

protected:
    void healHimself()
    {
		tickWithLowHealth(45);
        tickWithLowHealth(45);
		tickWithLowHealth(35);
        tickWithLowHealth(35);
        
        tick();
        tickInMeleeRange();

        assertActions(">S:chain heal>S:lesser healing wave>S:riptide>S:healing wave>T:reach melee>T:melee");
    }

    void healOthers()
    {
        tickWithPartyLowHealth(45);
        tickWithPartyLowHealth(45);
        tickWithPartyLowHealth(35);
		tickWithPartyLowHealth(35);

        assertActions(">P:chain heal on party>P:lesser healing wave on party>P:riptide on party>P:healing wave on party");
    }

    void buff()
    {
        removeAura("water shield");

        tick(); 
        addAura("water shield");

        removeAura("earthliving weapon");
        tick(); 
        tick(); 
        tick(); 
        tick(); 
        addAura("earthliving weapon");

        tickWithAttackerCount(3);
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);

        assertActions(">S:water shield>S:earthliving weapon>S:flametongue weapon>S:frostbrand weapon>S:rockbiter weapon>S:strength of earth totem>S:windfury totem>S:flametongue totem>S:mana spring totem");
    }

    void interruptSpell() 
    {
        tickWithTargetIsCastingNonMeleeSpell();
        
		assertActions(">T:wind shear");
    }

	void dispel() 
	{
		tickInMeleeRange();
		tickWithTargetAuraToDispel(DISPEL_MAGIC);

		assertActions(">T:melee>T:purge");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( HealShamanTestCase );
