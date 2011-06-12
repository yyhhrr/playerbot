#pragma once
using namespace std;

namespace ai
{
    class MockTargetValue : public ManualSetValue<Unit*>, public Qualified
    {
    public:
        MockTargetValue(AiManagerRegistry* const ai) : ManualSetValue<Unit*>(ai, NULL) {}
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
            return ai->GetStatsManager()->GetHealthPercent(target) < 100.0f ? target : NULL;
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
            creators["master target"] = &MockValueContext::mock;
            creators["line target"] = &MockValueContext::mock;
            creators["tank target"] = &MockValueContext::mock;
            creators["dps target"] = &MockValueContext::mock;
            creators["cc target"] = &MockValueContext::mock;
            creators["current cc target"] = &MockValueContext::mock;
            creators["pet target"] = &MockValueContext::mock;
            creators["grind target"] = &MockValueContext::mock;
        }

    private:
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
              GetValue<Unit*>("master target")->Set(MockedTargets::GetMaster());
              GetValue<Unit*>("line target")->Set(MockedTargets::GetLineTarget());
              GetValue<Unit*>("tank target")->Set(MockedTargets::GetTargetForTank());
              GetValue<Unit*>("dps target")->Set(MockedTargets::GetTargetForDps());
              GetValue<Unit*>("current cc target")->Set(NULL);
              GetValue<Unit*>("current target")->Set(MockedTargets::GetCurrentTarget());
              GetValue<Unit*>("pet target")->Set(MockedTargets::GetPet());

              //GetValue<Unit*>("party member without aura")->Set(MockedTargets.GetPartyMember());
              //GetValue<Unit*>("party member to heal")->Set(MockedTargets.GetPartyMember());
              //GetValue<Unit*>("party member to resurrect")->Set(MockedTargets.GetPartyMember());
              //GetValue<Unit*>("cc target")->Set(MockedTargets.GetCc());
              //GetValue<Unit*>("grind target")->Set(MockedTargets.GetCurrentTarget());
              //GetValue<Unit*>("party member to dispel")->Set(MockedTargets.GetPartyMember());
          }

    public:
        virtual UntypedValue* GetUntypedValue(const char* name) 
        {
            UntypedValue* value = mockValueContext.create(name, ai);
            return value ? value : realContext->GetUntypedValue(name);
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