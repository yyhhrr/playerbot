#pragma once
#include "../GenericTriggers.h"

namespace ai
{
    class ShamanWeaponTrigger : public BuffTrigger {
    public:
        ShamanWeaponTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "rockbiter weapon") {}
        virtual bool IsActive();
    };

    class TotemTrigger : public BuffTrigger {
    public:
        TotemTrigger(AiManagerRegistry* const ai, const char* spell) : BuffTrigger(ai, spell) {}
        virtual bool IsActive()
		{
            return BuffTrigger::IsActive() && statsManager->GetAttackerCount() > 2;
        }
    };

    class WindfuryTotemTrigger : public TotemTrigger {
    public:
        WindfuryTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "windfury totem") {}
    };

    class ManaSpringTotemTrigger : public TotemTrigger {
    public:
        ManaSpringTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "mana spring totem") {}
    };

    class FlametongueTotemTrigger : public TotemTrigger {
    public:
        FlametongueTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "flametongue totem") {}
    };

    class StrengthOfEarthTotemTrigger : public TotemTrigger {
    public:
        StrengthOfEarthTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "strength of earth totem") {}
    };

    class WindShearInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        WindShearInterruptSpellTrigger(AiManagerRegistry* const ai) : InterruptSpellTrigger(ai, "wind shear") {}
    };
    
    class WaterShieldTrigger : public BuffTrigger 
    {
    public:
        WaterShieldTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "water shield") {}
    };

    class LightningShieldTrigger : public BuffTrigger 
    {
    public:
        LightningShieldTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "lightning shield") {}
    };

    class PurgeTrigger : public TargetAuraDispelTrigger 
    {
    public:
        PurgeTrigger(AiManagerRegistry* const ai) : TargetAuraDispelTrigger(ai, "purge", DISPEL_MAGIC) {}
    };
}
