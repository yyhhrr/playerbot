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

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, shaman::StrategyFactoryInternal>
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
            Strategy* heal(AiManagerRegistry* ai) { return new HealShamanStrategy(ai); }
            Strategy* dps(AiManagerRegistry* ai) { return new MeleeShamanStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new ShamanNonCombatStrategy(ai); }
        }
        strategyFactoryInternal;
    };
};

Strategy* ShamanActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::shaman::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace shaman
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
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
            Trigger* windfury_totem(AiManagerRegistry* ai) { return new WindfuryTotemTrigger(ai); }
            Trigger* mana_spring_totem(AiManagerRegistry* ai) { return new ManaSpringTotemTrigger(ai); }
            Trigger* flametongue_totem(AiManagerRegistry* ai) { return new FlametongueTotemTrigger(ai); }
            Trigger* strength_of_earth_totem(AiManagerRegistry* ai) { return new StrengthOfEarthTotemTrigger(ai); }
            Trigger* wind_shear(AiManagerRegistry* ai) { return new WindShearInterruptSpellTrigger(ai); }
            Trigger* purge(AiManagerRegistry* ai) { return new PurgeTrigger(ai); }
            Trigger* shaman_weapon(AiManagerRegistry* ai) { return new ShamanWeaponTrigger(ai); }
            Trigger* water_shield(AiManagerRegistry* ai) { return new WaterShieldTrigger(ai); }
            Trigger* lightning_shield(AiManagerRegistry* ai) { return new LightningShieldTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* ShamanActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::shaman::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace shaman
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
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
            Action* water_shield(AiManagerRegistry* ai) { return new CastWaterShieldAction(ai); }
            Action* lightning_shield(AiManagerRegistry* ai) { return new CastLightningShieldAction(ai); }
            Action* strength_of_earth_totem(AiManagerRegistry* ai) { return new CastStrengthOfEarthTotemAction(ai); }
            Action* flametongue_totem(AiManagerRegistry* ai) { return new CastFlametongueTotemAction(ai); }
            Action* windfury_totem(AiManagerRegistry* ai) { return new CastWindfuryTotemAction(ai); }
            Action* mana_spring_totem(AiManagerRegistry* ai) { return new CastManaSpringTotemAction(ai); }
            Action* mana_tide_totem(AiManagerRegistry* ai) { return new CastManaTideTotemAction(ai); }
            Action* healing_stream_totem(AiManagerRegistry* ai) { return new CastHealingStreamTotemAction(ai); }
            Action* wind_shear(AiManagerRegistry* ai) { return new CastWindShearAction(ai); }
            Action* rockbiter_weapon(AiManagerRegistry* ai) { return new CastRockbiterWeaponAction(ai); }
            Action* flametongue_weapon(AiManagerRegistry* ai) { return new CastFlametongueWeaponAction(ai); }
            Action* frostbrand_weapon(AiManagerRegistry* ai) { return new CastFrostbrandWeaponAction(ai); }
            Action* windfury_weapon(AiManagerRegistry* ai) { return new CastWindfuryWeaponAction(ai); }
            Action* earthliving_weapon(AiManagerRegistry* ai) { return new CastEarthlivingWeaponAction(ai); }
            Action* purge(AiManagerRegistry* ai) { return new CastPurgeAction(ai); }
            Action* healing_wave(AiManagerRegistry* ai) { return new CastHealingWaveAction(ai); }
            Action* lesser_healing_wave(AiManagerRegistry* ai) { return new CastLesserHealingWaveAction(ai); }
            Action* healing_wave_on_party(AiManagerRegistry* ai) { return new CastHealingWaveOnPartyAction(ai); }
            Action* lesser_healing_wave_on_party(AiManagerRegistry* ai) { return new CastLesserHealingWaveOnPartyAction(ai); }
            Action* earth_shield(AiManagerRegistry* ai) { return new CastEarthShieldAction(ai); }
            Action* earth_shield_on_party(AiManagerRegistry* ai) { return new CastEarthShieldOnPartyAction(ai); }
            Action* chain_heal(AiManagerRegistry* ai) { return new CastChainHealAction(ai); }
            Action* riptide(AiManagerRegistry* ai) { return new CastRiptideAction(ai); }
            Action* chain_heal_on_party(AiManagerRegistry* ai) { return new CastChainHealOnPartyAction(ai); }
            Action* riptide_on_party(AiManagerRegistry* ai) { return new CastRiptideOnPartyAction(ai); }
            Action* stormstrike(AiManagerRegistry* ai) { return new CastStormstrikeAction(ai); }
            Action* lava_lash(AiManagerRegistry* ai) { return new CastLavaLashAction(ai); }
            Action* ancestral_spirit(AiManagerRegistry* ai) { return new CastAncestralSpiritAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* ShamanActionFactory::createAction(const char* name)
{
    Action* action = ai::shaman::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
