#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
	class MockPlayerbotAIBase : public PlayerbotAI
	{
	public:
		MockPlayerbotAIBase() : PlayerbotAI() 
        {
            targetIsCastingNonMeleeSpell = false;
            this->buffer = buffer;
        }
        void SetContext(AiObjectContext* context) { this->aiObjectContext = context; }
	
        virtual uint32 GetSpellId(const char* args) { return 1; }
        virtual void InterruptSpell();
        virtual void RemoveAura(const char* name);
        virtual bool CanCastSpell(const char* name, Unit* target);
        virtual bool CastSpell(const char* name, Unit* target);
        virtual bool HasAura(const char* spellName, Unit* player);
        virtual bool IsSpellCasting(Unit* player);
        virtual bool HasAuraToDispel(Unit* player, uint32 dispelType);
        virtual bool IsSpellCastUseful(const char* name, Unit* target);

    public:
        void resetSpells() {spellCooldowns.clear(); }

    public:
        string *buffer;

    public:
        list<string> spellCooldowns;

        map<Unit*, list<string>> auras;
        map<Unit*, uint32> dispels;

        bool targetIsCastingNonMeleeSpell;
    };

    class MockAiManagerRegistry : public AiManagerRegistry
    {
    public:
		MockAiManagerRegistry();
		virtual ~MockAiManagerRegistry();

    public:
        void SetContext(AiObjectContext* context) { GetMockAi()->SetContext(context); }
        MockPlayerbotAIBase* GetMockAi() { return (MockPlayerbotAIBase*)ai; }

	public:
		std::string buffer;
	};

}