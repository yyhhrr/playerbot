#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/rogue/RogueAiObjectContext.h"

using namespace ai;


class DpsRogueTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DpsRogueTestCase );
		CPPUNIT_TEST( combatVsMelee );
		CPPUNIT_TEST( healHimself );
		CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new RogueAiObjectContext(ai), "dps", NULL);
        addTargetAura("slice and dice");
    }

protected:
    void combatVsMelee()
    {
        removeTargetAura("slice and dice");

		tickOutOfMeleeRange();
		tickInMeleeRange();

		addTargetAura("slice and dice");

		tickWithEnergy(70);
        tickWithEnergy(70);
        tickWithEnergy(70);

        tickWithComboPoints(5);
        tickWithComboPoints(5);

        tickBehindTarget();
        
        assertActions(">T:reach melee>T:slice and dice>T:mutilate>T:sinister strike>T:melee>T:eviscerate>T:melee>T:backstab");
    }

	void healHimself()
	{
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithMyAttackerCount(3);

		assertActions(">S:evasion>S:feint>S:vanish");
	}

	void interruptSpells()
	{
        tickInMeleeRange();

		tickWithTargetIsCastingNonMeleeSpell();
		tickWithTargetIsCastingNonMeleeSpell();

		assertActions(">T:mutilate>T:kick>T:kidney shot");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsRogueTestCase );
