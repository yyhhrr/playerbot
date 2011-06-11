#pragma once;

#include "HealthTriggers.h"
#include "GenericTriggers.h"

namespace ai
{

    class TriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        TriggerContext()
        {
            creators["timer"] = &TriggerContext::Timer;
            creators["random"] = &TriggerContext::Random;

            creators["target critical health"] = &TriggerContext::TargetCriticalHealth;
            creators["critical health"] = &TriggerContext::CriticalHealth;
            creators["low health"] = &TriggerContext::LowHealth;
            creators["medium health"] = &TriggerContext::MediumHealth;
            creators["low mana"] = &TriggerContext::LowMana;

            creators["party member critical health"] = &TriggerContext::PartyMemberCriticalHealth;
            creators["party member low health"] = &TriggerContext::PartyMemberLowHealth;
            creators["party member medium health"] = &TriggerContext::PartyMemberMediumHealth;

            creators["light rage available"] = &TriggerContext::LightRageAvailable;
            creators["medium rage available"] = &TriggerContext::MediumRageAvailable;
            creators["high rage available"] = &TriggerContext::HighRageAvailable;

            creators["light energy available"] = &TriggerContext::LightEnergyAvailable;
            creators["medium energy available"] = &TriggerContext::MediumEnergyAvailable;
            creators["high energy available"] = &TriggerContext::HighEnergyAvailable;

            creators["loot available"] = &TriggerContext::LootAvailable;
            creators["no attackers"] = &TriggerContext::NoAttackers;
            creators["no target"] = &TriggerContext::NoTarget;

            creators["tank aoe"] = &TriggerContext::TankAoe;
            creators["lose aggro"] = &TriggerContext::LoseAggro;

            creators["light aoe"] = &TriggerContext::LightAoe;
            creators["medium aoe"] = &TriggerContext::MediumAoe;
            creators["high aoe"] = &TriggerContext::HighAoe;

            creators["enemy out of melee"] = &TriggerContext::EnemyOutOfMelee;
            creators["enemy out of spell"] = &TriggerContext::EnemyOutOfSpell;
            creators["enemy too close"] = &TriggerContext::EnemyTooClose;

            creators["combo points available"] = &TriggerContext::ComboPointsAvailable;

            creators["medium threat"] = &TriggerContext::MediumThreat;

            creators["party member dead"] = &TriggerContext::PartyMemberDead;
            creators["no pet"] = &TriggerContext::no_pet;
            creators["has attackers"] = &TriggerContext::has_attackers;

            creators["no drink"] = &TriggerContext::no_drink;
            creators["no food"] = &TriggerContext::no_food;

            creators["panic"] = &TriggerContext::panic;
            creators["behind target"] = &TriggerContext::behind_target;
        }

    private:
        static Trigger* behind_target(AiManagerRegistry* ai) { return new IsBehindTargetTrigger(ai); }
        static Trigger* panic(AiManagerRegistry* ai) { return new PanicTrigger(ai); }
        static Trigger* no_drink(AiManagerRegistry* ai) { return new NoDrinkTrigger(ai); }
        static Trigger* no_food(AiManagerRegistry* ai) { return new NoFoodTrigger(ai); }
        static Trigger* LightAoe(AiManagerRegistry* ai) { return new LightAoeTrigger(ai); }
        static Trigger* MediumAoe(AiManagerRegistry* ai) { return new MediumAoeTrigger(ai); }
        static Trigger* HighAoe(AiManagerRegistry* ai) { return new HighAoeTrigger(ai); }
        static Trigger* LoseAggro(AiManagerRegistry* ai) { return new LoseAggroTrigger(ai); }
        static Trigger* LowHealth(AiManagerRegistry* ai) { return new LowHealthTrigger(ai); }
        static Trigger* MediumHealth(AiManagerRegistry* ai) { return new MediumHealthTrigger(ai); }
        static Trigger* CriticalHealth(AiManagerRegistry* ai) { return new CriticalHealthTrigger(ai); }
        static Trigger* TargetCriticalHealth(AiManagerRegistry* ai) { return new TargetCriticalHealthTrigger(ai); }
        static Trigger* LowMana(AiManagerRegistry* ai) { return new LowManaTrigger(ai); }
        static Trigger* LightRageAvailable(AiManagerRegistry* ai) { return new LightRageAvailableTrigger(ai); }
        static Trigger* MediumRageAvailable(AiManagerRegistry* ai) { return new MediumRageAvailableTrigger(ai); }
        static Trigger* HighRageAvailable(AiManagerRegistry* ai) { return new HighRageAvailableTrigger(ai); }
        static Trigger* LightEnergyAvailable(AiManagerRegistry* ai) { return new LightEnergyAvailableTrigger(ai); }
        static Trigger* MediumEnergyAvailable(AiManagerRegistry* ai) { return new MediumEnergyAvailableTrigger(ai); }
        static Trigger* HighEnergyAvailable(AiManagerRegistry* ai) { return new HighEnergyAvailableTrigger(ai); }
        static Trigger* LootAvailable(AiManagerRegistry* ai) { return new LootAvailableTrigger(ai); }
        static Trigger* NoAttackers(AiManagerRegistry* ai) { return new NoAttackersTrigger(ai); }
        static Trigger* TankAoe(AiManagerRegistry* ai) { return new TankAoeTrigger(ai); }
        static Trigger* Timer(AiManagerRegistry* ai) { return new TimerTrigger(ai); }
        static Trigger* NoTarget(AiManagerRegistry* ai) { return new NoTargetTrigger(ai); }
        static Trigger* Random(AiManagerRegistry* ai) { return new RandomTrigger(ai); }
        static Trigger* EnemyOutOfMelee(AiManagerRegistry* ai) { return new EnemyOutOfMeleeTrigger(ai); }
        static Trigger* EnemyOutOfSpell(AiManagerRegistry* ai) { return new EnemyOutOfSpellRangeTrigger(ai); }
        static Trigger* EnemyTooClose(AiManagerRegistry* ai) { return new EnemyTooCloseTrigger(ai); }
        static Trigger* ComboPointsAvailable(AiManagerRegistry* ai) { return new ComboPointsAvailableTrigger(ai); }
        static Trigger* MediumThreat(AiManagerRegistry* ai) { return new MediumThreatTrigger(ai); }
        static Trigger* PartyMemberDead(AiManagerRegistry* ai) { return new PartyMemberDeadTrigger(ai); }
        static Trigger* PartyMemberLowHealth(AiManagerRegistry* ai) { return new PartyMemberLowHealthTrigger(ai); }
        static Trigger* PartyMemberMediumHealth(AiManagerRegistry* ai) { return new PartyMemberMediumHealthTrigger(ai); }
        static Trigger* PartyMemberCriticalHealth(AiManagerRegistry* ai) { return new PartyMemberCriticalHealthTrigger(ai); }
        static Trigger* no_pet(AiManagerRegistry* ai) { return new NoPetTrigger(ai); }
        static Trigger* has_attackers(AiManagerRegistry* ai) { return new HasAttackersTrigger(ai); }

    };
};