#pragma once
#include "../GenericTriggers.h"

namespace ai
{
	class DemonArmorTrigger : public BuffTrigger
	{
	public:
		DemonArmorTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "demon armor") {}
		virtual bool IsActive();
	};

    class SpellstoneTrigger : public BuffTrigger
    {
    public:
        SpellstoneTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "spellstone") {}
        virtual bool IsActive();
    };

    DEBUFF_TRIGGER(CurseOfAgonyTrigger, "curse of agony", "curse of agony");
    DEBUFF_TRIGGER(CorruptionTrigger, "corruption", "corruption");
    DEBUFF_TRIGGER(ImmolateTrigger, "immolate", "immolate");

    class ShadowTranceTrigger : public HasAuraTrigger
    {
    public:
        ShadowTranceTrigger(AiManagerRegistry* const ai) : HasAuraTrigger(ai, "shadow trance") {}
    };

    class BanishTrigger : public HasCcTargetTrigger
    {
    public:
        BanishTrigger(AiManagerRegistry* const ai) : HasCcTargetTrigger(ai, "banish") {}
    };

    class HasSpellstoneTrigger : public ItemCountTrigger
    {
    public:
        HasSpellstoneTrigger(AiManagerRegistry* const ai) : ItemCountTrigger(ai, "spellstone", 1) {}
    };

    class HasFirestoneTrigger : public ItemCountTrigger
    {
    public:
        HasFirestoneTrigger(AiManagerRegistry* const ai) : ItemCountTrigger(ai, "firestone", 1) {}
    };

    class HasHealthstoneTrigger : public ItemCountTrigger
    {
    public:
        HasHealthstoneTrigger(AiManagerRegistry* const ai) : ItemCountTrigger(ai, "healthstone", 1) {}
    };
}