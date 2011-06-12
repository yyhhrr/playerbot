#include "pch.h"
#include "aitest.h"
#include "EngineTestBase.h"
#include "MockedTargets.h"
#include "AiObjectContextWrapper.h"

class TestActionExecutionListener : public ActionExecutionListener
{
public:
    TestActionExecutionListener(MockAiManagerRegistry *ai) : ai(ai) {}

    virtual void Before(Action* action) {}
    virtual bool AllowExecution(Action* action) { return false; }
    virtual bool OverrideResult(bool executed) { return true; }
    virtual void After(Action* action) 
    {
        ai->buffer.append(">");        
        MockedTargets::Append(ai->buffer, action->GetTarget());
        ai->buffer.append(":");
        ai->buffer.append(action->getName());

        ((MockAiSpellManager*)ai->GetSpellManager())->spellCooldowns.push_back(action->getName()); 
    }

private:
    MockAiManagerRegistry *ai;
};


void EngineTestBase::setUp()
{
	ai = new MockAiManagerRegistry();
	spellManager = (MockAiSpellManager*)ai->GetSpellManager();
	moveManager = (MockAiMoveManager*)ai->GetMoveManager();
	inventoryManager = (MockAiInventoryManager*)ai->GetInventoryManager();
	socialManager = (MockAiSocialManager*)ai->GetSocialManager();
}

void EngineTestBase::tearDown()
{
    if (engine)
        delete engine;
    if (ai) 
        delete ai;
}

void EngineTestBase::va_generic(void (EngineTestBase::*callback)(const char*), va_list vl)
{
	const char* cur = NULL;
	do 
	{
		cur = va_arg(vl, const char*);
		if (cur)
			(this->*callback)(cur);
	}
	while (cur);

	va_end(vl);
}


void EngineTestBase::setupEngine(AiObjectContext* aiObjectContext, ...)
{
    context = new AiObjectContextWrapper(ai, aiObjectContext);
    ai->SetContext(context);
    engine = new Engine(ai, context);
    //engine->AddActionExecutionListener(new TestActionExecutionListener(ai));
    
	va_list vl;
	va_start(vl, aiObjectContext);

	va_generic(&EngineTestBase::setupEngineCallback, vl);
    
	engine->testMode = true;
	engine->Init();
}

void EngineTestBase::setupEngineCallback(const char* name)
{
	engine->addStrategy(name);
}

void EngineTestBase::tick() 
{
	engine->DoNextAction(NULL);
}

void EngineTestBase::assertActions(const char* expected) 
{
	bool pass = ai->buffer == expected;
	if (!pass)
	{
		std::cout << "\n===\n";
		std::cout << "Exp: " << expected << "\n";
		std::cout << "Act: " << ai->buffer << "\n";
		std::cout << "===\n";
	}
    CPPUNIT_ASSERT(pass);
}

void EngineTestBase::tickWithNoTarget()
{
    context->GetValue<Unit*>("current target")->Set(NULL);
    set<uint8>("my attacker count", 0);
    
	tick();
    
    set<uint8>("my attacker count", 1);
    context->GetValue<Unit*>("current target")->Set(MockedTargets::GetCurrentTarget());
}

void EngineTestBase::spellUnavailable(const char* spell)
{
	spellManager->spellCooldowns.push_back(spell);
}

void EngineTestBase::tickWithSpellUnavailable(const char* spell)
{
	spellUnavailable(spell);
	tick();
}

void EngineTestBase::tickWithSpellAvailable(const char* spell) 
{
	spellAvailable(spell);
	tick();
}

void EngineTestBase::spellAvailable(const char* spell)
{
	spellManager->spellCooldowns.remove(spell);
}

void EngineTestBase::addAura(const char* spell)
{
	spellManager->auras[MockedTargets::GetSelf()].push_back(spell);
}

void EngineTestBase::removeAura(const char* spell)
{
	spellManager->auras[MockedTargets::GetSelf()].remove(spell);
}

void EngineTestBase::tickOutOfSpellRange()
{
	moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 49.0f;
    tick(); 
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f;	
}

void EngineTestBase::tickOutOfMeleeRange()
{
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f;
    tick(); 
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0.0f;	
}

void EngineTestBase::tickInMeleeRange()
{
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0.0f;
	tick();
}

void EngineTestBase::tickWithNoAggro()
{
    set<bool>("has aggro", "current target", false);
    tick();
    set<bool>("has aggro", "current target", true);
}

void EngineTestBase::tickWithRage(int amount)
{
    set<uint8>("rage", "self target", amount);
    tick();
    set<uint8>("rage", "self target", 0);
}

void EngineTestBase::tickWithEnergy(int amount)
{
    set<uint8>("energy", "self target", amount);
	tick();
    set<uint8>("energy", "self target", 0);
}

void EngineTestBase::tickWithAttackerCount(int count)
{
    set<uint8>("attacker count", count);
	tick();
    set<uint8>("attacker count", 1);
}

void EngineTestBase::tickWithMyAttackerCount(int count)
{
    set<uint8>("my attacker count", count);
	tickWithAttackerCount(count + 1);
    set<uint8>("my attacker count", 1);
}

void EngineTestBase::tickWithLowHealth(int amount)
{
	lowHealth(amount);
	tick();
	healthRestored();
}

void EngineTestBase::tickWithPartyLowHealth(int amount)
{
    set<uint8>("health", "party member to heal", amount);
	tick();
    set<uint8>("health", "party member to heal", 100);
}

void EngineTestBase::tickWithAuraToDispel(uint32 type)
{
	spellManager->dispels[MockedTargets::GetSelf()] = type;
	tick();
	spellManager->dispels[MockedTargets::GetSelf()] = 0;
}

void EngineTestBase::tickWithPartyAuraToDispel(uint32 type)
{
	spellManager->dispels[MockedTargets::GetPartyMember()] = type;
	tick();
	spellManager->dispels[MockedTargets::GetPartyMember()] = 0;
}

void EngineTestBase::tickWithTargetAuraToDispel(uint32 type)
{
	spellManager->dispels[MockedTargets::GetCurrentTarget()] = type;
	tick();
	spellManager->dispels[MockedTargets::GetCurrentTarget()] = 0;
}

void EngineTestBase::lowHealth(int amount)
{
    set<uint8>("health", "self target", amount);
}

void EngineTestBase::lowMana(int amount)
{
    set<uint8>("mana", "self target", amount);
}

void EngineTestBase::healthRestored()
{
    set<uint8>("health", "self target", 100);
}

void EngineTestBase::tickWithComboPoints(int amount)
{
    set<uint8>("combo", "self target", amount);
	tick();
    set<uint8>("combo", "self target", 0);
}

void EngineTestBase::tickWithTargetIsCastingNonMeleeSpell() 
{
    spellManager->targetIsCastingNonMeleeSpell = true;
    tick();
    spellManager->targetIsCastingNonMeleeSpell = false;
}

void EngineTestBase::tickWithBalancePercent(int percent)
{
    set<uint8>("balance", percent);
	tick();
    set<uint8>("balance", 100);
}

void EngineTestBase::tickWithNoPet()
{
    context->GetValue<Unit*>("pet target")->Set(NULL);
	tick();
    context->GetValue<Unit*>("pet target")->Set(MockedTargets::GetPet());
}

void EngineTestBase::tickWithPetLowHealth(int amount)
{
    set<uint8>("health", "pet target", amount);
	tick();
    set<uint8>("health", "pet target", 100);
}

void EngineTestBase::tickWithPetDead()
{
    set<bool>("dead", "pet target", true);
    tick();
    set<bool>("dead", "pet target", false);
}

void EngineTestBase::tickWithLowMana(int amount)
{
    set<uint8>("mana", "self target", amount);
    tick();
    set<uint8>("mana", "self target", 100);
}

void EngineTestBase::tickWithTargetLowHealth(int amount)
{
    set<uint8>("health", "current target", amount);
    tick();
    set<uint8>("health", "current target", 100);
}
void EngineTestBase::tickWithTargetIsMoving()
{
    moveManager->moving[MockedTargets::GetCurrentTarget()] = true;
    tick();
    moveManager->moving[MockedTargets::GetCurrentTarget()] = false;
}

void EngineTestBase::tickInSpellRange()
{
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f;
    tick();
}

void EngineTestBase::addTargetAura(const char* spell)
{
	spellManager->auras[MockedTargets::GetCurrentTarget()].push_back(spell);
}

void EngineTestBase::removeTargetAura(const char* spell)
{
    spellManager->auras[MockedTargets::GetCurrentTarget()].remove(spell);
}

void EngineTestBase::addPartyAura(const char* spell)
{
    spellManager->auras[MockedTargets::GetPartyMember()].push_back(spell);
}

void EngineTestBase::removePartyAura(const char* spell)
{
    spellManager->auras[MockedTargets::GetPartyMember()].remove(spell);
}

void EngineTestBase::tickWithLootAvailable()
{
	inventoryManager->lootAvailable = true;
	tick();
	inventoryManager->lootAvailable = false;
}

void EngineTestBase::tickWithNoDrink()
{
	inventoryManager->hasDrink = false;
	tick();
	inventoryManager->hasDrink = true;
}

void EngineTestBase::tickWithNoFood()
{
	inventoryManager->hasFood = false;
	tick();
	inventoryManager->hasFood = true;
}

void EngineTestBase::itemAvailable(const char* item, int amount)
{
	inventoryManager->itemCounts[std::string(item)] = amount;
}

void EngineTestBase::tickWithDeadPartyMember() 
{
    context->GetValue<Unit*>("party member to resurrect")->Set(MockedTargets::GetPartyMember());
	tick();
    context->GetValue<Unit*>("party member to resurrect")->Set(NULL);
}

void EngineTestBase::tickBehindTarget()
{
    moveManager->isBehind[MockedTargets::GetCurrentTarget()] = true;
    tick();
    moveManager->isBehind[MockedTargets::GetCurrentTarget()] = false;
}

void EngineTestBase::tickWithCcTarget(const char* spell)
{   
    set<uint8>("attacker count", 3);
    context->GetValue<Unit*>("cc target", spell)->Set(MockedTargets::GetCc());
    tick();
    set<uint8>("attacker count", 1);
    context->GetValue<Unit*>("cc target", spell)->Set(NULL);
}
