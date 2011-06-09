#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanActions.h"
#include "ShamanActionFactory.h"
#include "ShamanNonCombatStrategy.h"
#include "HealShamanStrategy.h"
#include "MeleeShamanStrategy.h"
#include "ShamanTriggers.h"
#include "../NamedObjectFactory.h"

using namespace ai;



namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
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

        class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
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

        class ActionFactoryInternal : public NamedObjectFactory<Action>
        {
        public:
            ActionFactoryInternal()
            {
                creators["water shield"] = &ActionFactoryInternal::water_shield;
                creators["lightning shield"] = &ActionFactoryInternal::lightning_shield;
                creators["strength of earth totem"] = &ActionFactoryInternal::strength_of_earth_totem;
                creators["flametongue totem"] = &ActionFactoryInternal::flametongue_totem;
                creators["windfury totem"] = &ActionFactoryInternal::windfury_totem;
                creators["mana spring totem"] = &ActionFactoryInternal::mana_spring_totem;
                creators["mana tide totem"] = &ActionFactoryInternal::mana_tide_totem;
                creators["healing stream totem"] = &ActionFactoryInternal::healing_stream_totem;
                creators["wind shear"] = &ActionFactoryInternal::wind_shear;
                creators["rockbiter weapon"] = &ActionFactoryInternal::rockbiter_weapon;
                creators["flametongue weapon"] = &ActionFactoryInternal::flametongue_weapon;
                creators["frostbrand weapon"] = &ActionFactoryInternal::frostbrand_weapon;
                creators["windfury weapon"] = &ActionFactoryInternal::windfury_weapon;
                creators["earthliving weapon"] = &ActionFactoryInternal::earthliving_weapon;
                creators["purge"] = &ActionFactoryInternal::purge;
                creators["healing wave"] = &ActionFactoryInternal::healing_wave;
                creators["lesser healing wave"] = &ActionFactoryInternal::lesser_healing_wave;
                creators["healing wave on party"] = &ActionFactoryInternal::healing_wave_on_party;
                creators["lesser healing wave on party"] = &ActionFactoryInternal::lesser_healing_wave_on_party;
                creators["earth shield"] = &ActionFactoryInternal::earth_shield;
                creators["earth shield on party"] = &ActionFactoryInternal::earth_shield_on_party;
                creators["chain heal"] = &ActionFactoryInternal::chain_heal;
                creators["riptide"] = &ActionFactoryInternal::riptide;
                creators["chain heal on party"] = &ActionFactoryInternal::chain_heal_on_party;
                creators["riptide on party"] = &ActionFactoryInternal::riptide_on_party;
                creators["stormstrike"] = &ActionFactoryInternal::stormstrike;
                creators["lava lash"] = &ActionFactoryInternal::lava_lash;
                creators["ancestral spirit"] = &ActionFactoryInternal::ancestral_spirit;
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



ShamanActionFactory::ShamanActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai)
{
    strategyFactories.push_back(new ai::shaman::StrategyFactoryInternal());
    actionFactories.push_back(new ai::shaman::ActionFactoryInternal());
    triggerFactories.push_back(new ai::shaman::TriggerFactoryInternal());    
}