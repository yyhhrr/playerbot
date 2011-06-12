#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warrior/WarriorAiObjectContext.h"

using namespace ai;


class TankWarriorTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( TankWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( healing );
	CPPUNIT_TEST( snare );
    CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarriorAiObjectContext(ai), "tank", NULL);

        // this buff is combat-only, so skip for most test cases
        addAura("battle shout");
        set<uint8>("rage", "self target", 20);
		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0;
    }

protected:
    void interruptSpells() 
    {
		tickWithTargetIsCastingNonMeleeSpell();
        
        tick(); // rend

        assertActions(">T:shield bash>S:defensive stance");
    }

    void healing()
    {
        tickWithLowHealth(50); // defensive stance
        tickWithLowHealth(50); // shield wall
        tickWithLowHealth(50); // shield block

		tickWithLowHealth(4); 
		tickWithLowHealth(4); 

		assertActions(">S:defensive stance>T:shield wall>S:shield block>S:last stand>T:intimidating shout");
    }

    void buff()
    {
        set<uint8>("rage", "self target", 0);
        removeAura("battle shout");

        tickInSpellRange(); // battle shout

        tickInSpellRange(); // defensive stance
        tickInSpellRange(); // reach melee
        
		
        tickInMeleeRange(); // bloodrage
        tick(); // melee
        tick(); // battle shout

		assertActions(">S:battle shout>S:defensive stance>T:reach melee>T:melee>S:bloodrage>T:rend");

    }

    void warriorMustDemoralizeAttackers()
    {
        addAura("defensive stance");

        tick(); // melee

		tickWithAttackerCount(3); // shockwave
		tickWithAttackerCount(2); // demoralizing shout
		tickWithAttackerCount(2); // thunder clap

        assertActions(">T:melee>T:shockwave>T:demoralizing shout>T:thunder clap");
    }

    void warriorMustHoldAggro()
    {
        tickWithSpellAvailable("defensive stance");
        tick(); // melee

		tickWithNoAggro();
        
        tick(); // rend
        
        tick();

		assertActions(">S:defensive stance>T:melee>T:taunt>T:devastate>T:revenge");
    }

    void combatVsMelee()
    {
		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f; // enemy too far
        set<uint8>("rage", "self target", 11);
        
        tick(); // defensive stance
        tick(); // reach melee
        moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0.0f; 
        tick(); // melee

        tick(); // bloodrage
        tick(); // rend
        spellAvailable("rend");
        addTargetAura("rend");

        set<uint8>("rage", "self target", 21);
        tick(); // devastate
        tick(); // revenge
        tick(); // sunder armor

        set<uint8>("rage", "self target", 41);
		tick(); //shield slam

        tick(); // disarm
        tick(); // heroic strike
        spellAvailable("disarm");
        addTargetAura("disarm");

        tick(); 
        spellAvailable("disarm");
        addTargetAura("disarm");
        spellAvailable("devastate");

        tick(); 
        spellAvailable("sunder armor");
        addTargetAura("sunder armor");

		tick(); 

        spellAvailable("heroic strike");
        tick(); 
        set<uint8>("rage", "self target", 20);

        addAura("sword and board");
        tickWithSpellAvailable("shield slam");

		assertActions(">S:defensive stance>T:reach melee>T:melee>S:bloodrage>T:rend>T:devastate>T:revenge>T:sunder armor>T:shield slam>T:heroic strike>T:disarm>T:melee>T:devastate>T:slam>T:heroic strike>T:shield slam");
    }

    void revengeIfDodge()
    {
        tick(); // melee
        spellAvailable("revenge");
        tick(); // defensive stance
        tick(); // revenge

		assertActions(">T:melee>S:defensive stance>T:revenge");
    }

	void snare()
	{
		tick();
		tick();
		tickWithTargetIsMoving();
		
		assertActions(">S:defensive stance>T:melee>T:concussion blow");
	}
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarriorTestCase );
