#pragma once
#include "../GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(ArcaneIntellectOnPartyTrigger, "arcane intellect", "arcane intellect on party")
    BUFF_TRIGGER(ArcaneIntellectTrigger, "arcane intellect", "arcane intellect")

    class MageArmorTrigger : public BuffTrigger {
    public:
        MageArmorTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "mage armor") {}
        virtual bool IsActive();
    };

    class FireballTrigger : public DebuffTrigger {
    public:
        FireballTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "fireball") {}
	};

    class PyroblastTrigger : public DebuffTrigger {
    public:
        PyroblastTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "pyroblast") {}
    };

    class CounterspellInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        CounterspellInterruptSpellTrigger(AiManagerRegistry* const ai) : InterruptSpellTrigger(ai, "counterspell") {}
    };

    class CombustionTrigger : public BoostTrigger
    {
    public:
        CombustionTrigger(AiManagerRegistry* const ai) : BoostTrigger(ai, "combustion") {}
    };

    class IcyVeinsTrigger : public BoostTrigger
    {
    public:
        IcyVeinsTrigger(AiManagerRegistry* const ai) : BoostTrigger(ai, "icy veins") {}
    };
    
    class PolymorphTrigger : public HasCcTargetTrigger
    {
    public:
        PolymorphTrigger(AiManagerRegistry* const ai) : HasCcTargetTrigger(ai, "polymorph") {}
    };

    class RemoveCurseTrigger : public NeedCureTrigger 
    {
    public:
        RemoveCurseTrigger(AiManagerRegistry* const ai) : NeedCureTrigger(ai, "remove curse", DISPEL_MAGIC) {}
    };

    class PartyMemberRemoveCurseTrigger : public PartyMemberNeedCureTrigger 
    {
    public:
        PartyMemberRemoveCurseTrigger(AiManagerRegistry* const ai) : PartyMemberNeedCureTrigger(ai, "remove curse", DISPEL_MAGIC) {}
    };
    
    class SpellstealTrigger : public TargetAuraDispelTrigger 
    {
    public:
        SpellstealTrigger(AiManagerRegistry* const ai) : TargetAuraDispelTrigger(ai, "spellsteal", DISPEL_MAGIC) {}
    };
    
}
