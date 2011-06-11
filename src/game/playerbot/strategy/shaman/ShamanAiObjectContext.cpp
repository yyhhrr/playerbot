#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanActions.h"
#include "ShamanAiObjectContext.h"
#include "ShamanNonCombatStrategy.h"
#include "HealShamanStrategy.h"
#include "MeleeShamanStrategy.h"
#include "ShamanTriggers.h"
#include "../NamedObjectContext.h"

using namespace ai;



namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["heal"] = &shaman::StrategyFactoryInternal::heal;
                creators["melee"] = &shaman::StrategyFactoryInternal::dps;
                creators["dps"] = &shaman::StrategyFactoryInternal::dps;
                creators["nc"] = &shaman::StrategyFactoryInternal::nc;
            }

        private:
            static Strategy* heal(AiManagerRegistry* ai) { return new HealShamanStrategy(ai); }
            static Strategy* dps(AiManagerRegistry* ai) { return new MeleeShamanStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new ShamanNonCombatStrategy(ai); }
        };
    };
};

namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["windfury totem"] = &TriggerFactoryInternal::windfury_totem;
                creators["mana spring totem"] = &TriggerFactoryInternal::mana_spring_totem;
                creators["flametongue totem"] = &TriggerFactoryInternal::flametongue_totem;
                creators["strength of earth totem"] = &TriggerFactoryInternal::strength_of_earth_totem;
                creators["wind shear"] = &TriggerFactoryInternal::wind_shear;
                creators["purge"] = &TriggerFactoryInternal::purge;
                creators["shaman weapon"] = &TriggerFactoryInternal::shaman_weapon;
                creators["water shield"] = &TriggerFactoryInternal::water_shield;
                creators["lightning shield"] = &TriggerFactoryInternal::lightning_shield;

            }

        private:
            static Trigger* windfury_totem(AiManagerRegistry* ai) { return new WindfuryTotemTrigger(ai); }
            static Trigger* mana_spring_totem(AiManagerRegistry* ai) { return new ManaSpringTotemTrigger(ai); }
            static Trigger* flametongue_totem(AiManagerRegistry* ai) { return new FlametongueTotemTrigger(ai); }
            static Trigger* strength_of_earth_totem(AiManagerRegistry* ai) { return new StrengthOfEarthTotemTrigger(ai); }
            static Trigger* wind_shear(AiManagerRegistry* ai) { return new WindShearInterruptSpellTrigger(ai); }
            static Trigger* purge(AiManagerRegistry* ai) { return new PurgeTrigger(ai); }
            static Trigger* shaman_weapon(AiManagerRegistry* ai) { return new ShamanWeaponTrigger(ai); }
            static Trigger* water_shield(AiManagerRegistry* ai) { return new WaterShieldTrigger(ai); }
            static Trigger* lightning_shield(AiManagerRegistry* ai) { return new LightningShieldTrigger(ai); }
        };
    };
};


namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["water shield"] = &AiObjectContextInternal::water_shield;
                creators["lightning shield"] = &AiObjectContextInternal::lightning_shield;
                creators["strength of earth totem"] = &AiObjectContextInternal::strength_of_earth_totem;
                creators["flametongue totem"] = &AiObjectContextInternal::flametongue_totem;
                creators["windfury totem"] = &AiObjectContextInternal::windfury_totem;
                creators["mana spring totem"] = &AiObjectContextInternal::mana_spring_totem;
                creators["mana tide totem"] = &AiObjectContextInternal::mana_tide_totem;
                creators["healing stream totem"] = &AiObjectContextInternal::healing_stream_totem;
                creators["wind shear"] = &AiObjectContextInternal::wind_shear;
                creators["rockbiter weapon"] = &AiObjectContextInternal::rockbiter_weapon;
                creators["flametongue weapon"] = &AiObjectContextInternal::flametongue_weapon;
                creators["frostbrand weapon"] = &AiObjectContextInternal::frostbrand_weapon;
                creators["windfury weapon"] = &AiObjectContextInternal::windfury_weapon;
                creators["earthliving weapon"] = &AiObjectContextInternal::earthliving_weapon;
                creators["purge"] = &AiObjectContextInternal::purge;
                creators["healing wave"] = &AiObjectContextInternal::healing_wave;
                creators["lesser healing wave"] = &AiObjectContextInternal::lesser_healing_wave;
                creators["healing wave on party"] = &AiObjectContextInternal::healing_wave_on_party;
                creators["lesser healing wave on party"] = &AiObjectContextInternal::lesser_healing_wave_on_party;
                creators["earth shield"] = &AiObjectContextInternal::earth_shield;
                creators["earth shield on party"] = &AiObjectContextInternal::earth_shield_on_party;
                creators["chain heal"] = &AiObjectContextInternal::chain_heal;
                creators["riptide"] = &AiObjectContextInternal::riptide;
                creators["chain heal on party"] = &AiObjectContextInternal::chain_heal_on_party;
                creators["riptide on party"] = &AiObjectContextInternal::riptide_on_party;
                creators["stormstrike"] = &AiObjectContextInternal::stormstrike;
                creators["lava lash"] = &AiObjectContextInternal::lava_lash;
                creators["ancestral spirit"] = &AiObjectContextInternal::ancestral_spirit;
            }

        private:
            static Action* water_shield(AiManagerRegistry* ai) { return new CastWaterShieldAction(ai); }
            static Action* lightning_shield(AiManagerRegistry* ai) { return new CastLightningShieldAction(ai); }
            static Action* strength_of_earth_totem(AiManagerRegistry* ai) { return new CastStrengthOfEarthTotemAction(ai); }
            static Action* flametongue_totem(AiManagerRegistry* ai) { return new CastFlametongueTotemAction(ai); }
            static Action* windfury_totem(AiManagerRegistry* ai) { return new CastWindfuryTotemAction(ai); }
            static Action* mana_spring_totem(AiManagerRegistry* ai) { return new CastManaSpringTotemAction(ai); }
            static Action* mana_tide_totem(AiManagerRegistry* ai) { return new CastManaTideTotemAction(ai); }
            static Action* healing_stream_totem(AiManagerRegistry* ai) { return new CastHealingStreamTotemAction(ai); }
            static Action* wind_shear(AiManagerRegistry* ai) { return new CastWindShearAction(ai); }
            static Action* rockbiter_weapon(AiManagerRegistry* ai) { return new CastRockbiterWeaponAction(ai); }
            static Action* flametongue_weapon(AiManagerRegistry* ai) { return new CastFlametongueWeaponAction(ai); }
            static Action* frostbrand_weapon(AiManagerRegistry* ai) { return new CastFrostbrandWeaponAction(ai); }
            static Action* windfury_weapon(AiManagerRegistry* ai) { return new CastWindfuryWeaponAction(ai); }
            static Action* earthliving_weapon(AiManagerRegistry* ai) { return new CastEarthlivingWeaponAction(ai); }
            static Action* purge(AiManagerRegistry* ai) { return new CastPurgeAction(ai); }
            static Action* healing_wave(AiManagerRegistry* ai) { return new CastHealingWaveAction(ai); }
            static Action* lesser_healing_wave(AiManagerRegistry* ai) { return new CastLesserHealingWaveAction(ai); }
            static Action* healing_wave_on_party(AiManagerRegistry* ai) { return new CastHealingWaveOnPartyAction(ai); }
            static Action* lesser_healing_wave_on_party(AiManagerRegistry* ai) { return new CastLesserHealingWaveOnPartyAction(ai); }
            static Action* earth_shield(AiManagerRegistry* ai) { return new CastEarthShieldAction(ai); }
            static Action* earth_shield_on_party(AiManagerRegistry* ai) { return new CastEarthShieldOnPartyAction(ai); }
            static Action* chain_heal(AiManagerRegistry* ai) { return new CastChainHealAction(ai); }
            static Action* riptide(AiManagerRegistry* ai) { return new CastRiptideAction(ai); }
            static Action* chain_heal_on_party(AiManagerRegistry* ai) { return new CastChainHealOnPartyAction(ai); }
            static Action* riptide_on_party(AiManagerRegistry* ai) { return new CastRiptideOnPartyAction(ai); }
            static Action* stormstrike(AiManagerRegistry* ai) { return new CastStormstrikeAction(ai); }
            static Action* lava_lash(AiManagerRegistry* ai) { return new CastLavaLashAction(ai); }
            static Action* ancestral_spirit(AiManagerRegistry* ai) { return new CastAncestralSpiritAction(ai); }
        };
    };
};



ShamanAiObjectContext::ShamanAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::shaman::StrategyFactoryInternal());
    actionContexts.Add(new ai::shaman::AiObjectContextInternal());
    triggerContexts.Add(new ai::shaman::TriggerFactoryInternal());    
}