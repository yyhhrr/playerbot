#pragma once
using namespace std;

namespace ai
{
    class MockTargetValue : public ManualSetValue<Unit*>, public Qualified
    {
    public:
        MockTargetValue(AiManagerRegistry* const ai) : ManualSetValue<Unit*>(ai, NULL) {}
    };

    class MockStatsValue : public ManualSetValue<uint8>, public Qualified
    {
    public:
        MockStatsValue(AiManagerRegistry* const ai) : ManualSetValue<uint8>(ai, 0) {}
    };

    class MockLogicalValue : public ManualSetValue<bool>, public Qualified
    {
    public:
        MockLogicalValue(AiManagerRegistry* const ai) : ManualSetValue<bool>(ai, false) {}
    };

    class MockPartyMemberWithoutAuraValue : public CalculatedValue<Unit*>, public Qualified
    {
    public:
        MockPartyMemberWithoutAuraValue(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}
        
        virtual Unit* Calculate()
        {
            const char* spell = qualifier.c_str();
            Unit* target = MockedTargets::GetPartyMember();
            return ai->GetSpellManager()->HasAura(spell, target) ? NULL : target;
        }
    };

    class MockPartyMemberToHeal : public CalculatedValue<Unit*>
    {
    public:
        MockPartyMemberToHeal(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}

        virtual Unit* Calculate()
        {
            Unit* target = MockedTargets::GetPartyMember();
            return AI_VALUE2(uint8, "health", "party member to heal") < 100.0f ? target : NULL;
        }
    };

    class MockPartyMemberToDispel : public CalculatedValue<Unit*>, public Qualified
    {
    public:
        MockPartyMemberToDispel(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}

        virtual Unit* Calculate()
        {
            uint32 dispelType = atoi(qualifier.c_str());
            Unit* target = MockedTargets::GetPartyMember();
            return ai->GetSpellManager()->HasAuraToDispel(target, dispelType) ? target : NULL;
        }
    };

    class MockValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        MockValueContext() : NamedObjectContext<UntypedValue>() 
        {
            creators["party member without aura"] = &MockValueContext::party_member_without_aura;
            creators["party member to heal"] = &MockValueContext::party_member_to_heal;
            creators["party member to dispel"] = &MockValueContext::party_member_to_dispel;
            creators["party member to resurrect"] = &MockValueContext::mock;
            creators["current target"] = &MockValueContext::mock;
            creators["self target"] = &MockValueContext::mock;
            creators["master"] = &MockValueContext::mock;
            creators["line target"] = &MockValueContext::mock;
            creators["tank target"] = &MockValueContext::mock;
            creators["dps target"] = &MockValueContext::mock;
            creators["cc target"] = &MockValueContext::mock;
            creators["current cc target"] = &MockValueContext::mock;
            creators["pet target"] = &MockValueContext::mock;
            creators["grind target"] = &MockValueContext::mock;
        
            creators["health"] = &MockValueContext::stats;
            creators["rage"] = &MockValueContext::stats;
            creators["energy"] = &MockValueContext::stats;
            creators["mana"] = &MockValueContext::stats;
            creators["combo"] = &MockValueContext::stats;
            creators["dead"] = &MockValueContext::logical;
            creators["has mana"] = &MockValueContext::logical;
        
            creators["attacker count"] = &MockValueContext::stats;
            creators["my attacker count"] = &MockValueContext::stats;
            creators["has aggro"] = &MockValueContext::logical;
            creators["balance"] = &MockValueContext::stats;
            creators["mounted"] = &MockValueContext::logical;
        }

    private:
        static UntypedValue* stats(AiManagerRegistry* ai) { return new MockStatsValue(ai); }
        static UntypedValue* logical(AiManagerRegistry* ai) { return new MockLogicalValue(ai); }
        static UntypedValue* mock(AiManagerRegistry* ai) { return new MockTargetValue(ai); }
        static UntypedValue* party_member_without_aura(AiManagerRegistry* ai) { return new MockPartyMemberWithoutAuraValue(ai); }
        static UntypedValue* party_member_to_heal(AiManagerRegistry* ai) { return new MockPartyMemberToHeal(ai); }
        static UntypedValue* party_member_to_dispel(AiManagerRegistry* ai) { return new MockPartyMemberToDispel(ai); }
    };

    class AiObjectContextWrapper : public AiObjectContext
    {
    public:
        AiObjectContextWrapper(AiManagerRegistry* const ai, AiObjectContext *realContext) : 
          AiObjectContext(ai), realContext(realContext) 
          {
              GetValue<Unit*>("self target")->Set(MockedTargets::GetSelf());
              GetValue<Unit*>("master")->Set(MockedTargets::GetMaster());
              GetValue<Unit*>("line target")->Set(MockedTargets::GetLineTarget());
              GetValue<Unit*>("tank target")->Set(MockedTargets::GetTargetForTank());
              GetValue<Unit*>("dps target")->Set(MockedTargets::GetTargetForDps());
              GetValue<Unit*>("current cc target")->Set(NULL);
              GetValue<Unit*>("current target")->Set(MockedTargets::GetCurrentTarget());
              GetValue<Unit*>("pet target")->Set(MockedTargets::GetPet());

              GetValue<uint8>("health", "self target")->Set(100);
              GetValue<uint8>("health", "current target")->Set(100);
              GetValue<uint8>("health", "pet target")->Set(100);
              GetValue<uint8>("health", "party member to heal")->Set(100);
              GetValue<uint8>("health", "party member to resurrect")->Set(100);
          
              GetValue<uint8>("mana", "self target")->Set(100);
              GetValue<uint8>("mana", "current target")->Set(100);
              GetValue<uint8>("mana", "pet target")->Set(100);
              GetValue<uint8>("mana", "party member to heal")->Set(100);
              GetValue<uint8>("mana", "party member to resurrect")->Set(100);
          
              GetValue<bool>("has mana", "self target")->Set(true);
              GetValue<bool>("has mana", "current target")->Set(true);
              GetValue<bool>("has mana", "pet target")->Set(true);
              GetValue<bool>("has mana", "party member to heal")->Set(true);
              GetValue<bool>("has mana", "party member to resurrect")->Set(true);
          
              GetValue<uint8>("attacker count")->Set(1);
              GetValue<uint8>("my attacker count")->Set(1);
              GetValue<uint8>("balance")->Set(100);
              
              GetValue<bool>("has aggro", "current target")->Set(true);
          }

    public:
        virtual UntypedValue* GetUntypedValue(const char* name) 
        {
            UntypedValue* value = mockValueContext.create(name, ai);
            UntypedValue* real = realContext->GetUntypedValue(name);
            CPPUNIT_ASSERT(real);
            return value ? value : real;
        }
        virtual Strategy* GetStrategy(const char* name) { return realContext->GetStrategy(name); }
        virtual Trigger* GetTrigger(const char* name) { return realContext->GetTrigger(name); }
        virtual Action* GetAction(const char* name) { return realContext->GetAction(name); }
        virtual void Update()
        {
            mockValueContext.Update();
            realContext->Update();
        }

    private:
        AiObjectContext *realContext;
        MockValueContext mockValueContext;
    };

}