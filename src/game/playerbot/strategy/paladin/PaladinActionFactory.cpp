#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinActions.h"
#include "PaladinTriggers.h"
#include "PaladinActionFactory.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "TankPaladinStrategy.h"
#include "DpsPaladinStrategy.h"
#include "PaladinBuffStrategies.h"
#include "../NamedObjectFactory.h"

using namespace ai;

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, paladin::StrategyFactoryInternal>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["tank"] = &paladin::StrategyFactoryInternal::tank;
                creators["dps"] = &paladin::StrategyFactoryInternal::dps;
                creators["nc"] = &paladin::StrategyFactoryInternal::nc;
                creators["bhealth"] = &paladin::StrategyFactoryInternal::bhealth;
                creators["bmana"] = &paladin::StrategyFactoryInternal::bmana;
                creators["bdps"] = &paladin::StrategyFactoryInternal::bdps;
                creators["barmor"] = &paladin::StrategyFactoryInternal::barmor;
                creators["rshadow"] = &paladin::StrategyFactoryInternal::rshadow;
                creators["rfrost"] = &paladin::StrategyFactoryInternal::rfrost;
                creators["rfire"] = &paladin::StrategyFactoryInternal::rfire;
            }

        private:
            Strategy* tank(AiManagerRegistry* ai) { return new TankPaladinStrategy(ai); }
            Strategy* dps(AiManagerRegistry* ai) { return new DpsPaladinStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericPaladinNonCombatStrategy(ai); }
            Strategy* bhealth(AiManagerRegistry* ai) { return new PaladinBuffHealthStrategy(ai); }
            Strategy* bmana(AiManagerRegistry* ai) { return new PaladinBuffManaStrategy(ai); }
            Strategy* bdps(AiManagerRegistry* ai) { return new PaladinBuffDpsStrategy(ai); }
            Strategy* barmor(AiManagerRegistry* ai) { return new PaladinBuffArmorStrategy(ai); }
            Strategy* rshadow(AiManagerRegistry* ai) { return new PaladinShadowResistanceStrategy(ai); }
            Strategy* rfrost(AiManagerRegistry* ai) { return new PaladinFrostResistanceStrategy(ai); }
            Strategy* rfire(AiManagerRegistry* ai) { return new PaladinFireResistanceStrategy(ai); }
        }
        strategyFactoryInternal;
    };
};

Strategy* PaladinActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::paladin::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["judgement of wisdom"] = &TriggerFactoryInternal::judgement_of_wisdom;
                creators["judgement of light"] = &TriggerFactoryInternal::judgement_of_light;
                creators["blessing"] = &TriggerFactoryInternal::blessing;
                creators["seal"] = &TriggerFactoryInternal::seal;
                creators["art of war"] = &TriggerFactoryInternal::art_of_war;
                creators["blessing of kings on party"] = &TriggerFactoryInternal::blessing_of_kings_on_party;
                creators["crusader aura"] = &TriggerFactoryInternal::crusader_aura;
                creators["retribution aura"] = &TriggerFactoryInternal::retribution_aura;
                creators["devotion aura"] = &TriggerFactoryInternal::devotion_aura;
                creators["shadow resistance aura"] = &TriggerFactoryInternal::shadow_resistance_aura;
                creators["frost resistance aura"] = &TriggerFactoryInternal::frost_resistance_aura;
                creators["fire resistance aura"] = &TriggerFactoryInternal::fire_resistance_aura;
                creators["hammer of justice snare"] = &TriggerFactoryInternal::hammer_of_justice_snare;
                creators["hammer of justice interrupt"] = &TriggerFactoryInternal::hammer_of_justice_interrupt;
                creators["cleanse cure disease"] = &TriggerFactoryInternal::CleanseCureDisease;
                creators["cleanse party member cure disease"] = &TriggerFactoryInternal::CleanseCurePartyMemberDisease;
                creators["cleanse cure poison"] = &TriggerFactoryInternal::CleanseCurePoison;
                creators["cleanse party member cure poison"] = &TriggerFactoryInternal::CleanseCurePartyMemberPoison;
                creators["cleanse cure magic"] = &TriggerFactoryInternal::CleanseCureMagic;
                creators["cleanse party member cure magic"] = &TriggerFactoryInternal::CleanseCurePartyMemberMagic;
                creators["righteous fury"] = &TriggerFactoryInternal::righteous_fury;
                creators["holy shield"] = &TriggerFactoryInternal::holy_shield;
            }

        private:
            Trigger* holy_shield(AiManagerRegistry* ai) { return new HolyShieldTrigger(ai); }
            Trigger* righteous_fury(AiManagerRegistry* ai) { return new RighteousFuryTrigger(ai); }
            Trigger* judgement_of_wisdom(AiManagerRegistry* ai) { return new JudgementOfWisdomTrigger(ai); }
            Trigger* judgement_of_light(AiManagerRegistry* ai) { return new JudgementOfLightTrigger(ai); }
            Trigger* blessing(AiManagerRegistry* ai) { return new BlessingTrigger(ai); }
            Trigger* seal(AiManagerRegistry* ai) { return new SealTrigger(ai); }
            Trigger* art_of_war(AiManagerRegistry* ai) { return new ArtOfWarTrigger(ai); }
            Trigger* blessing_of_kings_on_party(AiManagerRegistry* ai) { return new BlessingOfKingsOnPartyTrigger(ai); }
            Trigger* crusader_aura(AiManagerRegistry* ai) { return new CrusaderAuraTrigger(ai); }
            Trigger* retribution_aura(AiManagerRegistry* ai) { return new RetributionAuraTrigger(ai); }
            Trigger* devotion_aura(AiManagerRegistry* ai) { return new DevotionAuraTrigger(ai); }
            Trigger* shadow_resistance_aura(AiManagerRegistry* ai) { return new ShadowResistanceAuraTrigger(ai); }
            Trigger* frost_resistance_aura(AiManagerRegistry* ai) { return new FrostResistanceAuraTrigger(ai); }
            Trigger* fire_resistance_aura(AiManagerRegistry* ai) { return new FireResistanceAuraTrigger(ai); }
            Trigger* hammer_of_justice_snare(AiManagerRegistry* ai) { return new HammerOfJusticeSnareTrigger(ai); }
            Trigger* hammer_of_justice_interrupt(AiManagerRegistry* ai) { return new HammerOfJusticeInterruptSpellTrigger(ai); }
            Trigger* CleanseCureDisease(AiManagerRegistry* ai) { return new CleanseCureDiseaseTrigger(ai); }
            Trigger* CleanseCurePartyMemberDisease(AiManagerRegistry* ai) { return new CleanseCurePartyMemberDiseaseTrigger(ai); }
            Trigger* CleanseCurePoison(AiManagerRegistry* ai) { return new CleanseCurePoisonTrigger(ai); }
            Trigger* CleanseCurePartyMemberPoison(AiManagerRegistry* ai) { return new CleanseCurePartyMemberPoisonTrigger(ai); }
            Trigger* CleanseCureMagic(AiManagerRegistry* ai) { return new CleanseCureMagicTrigger(ai); }
            Trigger* CleanseCurePartyMemberMagic(AiManagerRegistry* ai) { return new CleanseCurePartyMemberMagicTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* PaladinActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::paladin::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace paladin
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
        {
        public:
            ActionFactoryInternal()
            {
                creators["seal of command"] = &ActionFactoryInternal::seal_of_command;
                creators["blessing of might"] = &ActionFactoryInternal::blessing_of_might;
                creators["divine storm"] = &ActionFactoryInternal::divine_storm;
                creators["blessing of kings on party"] = &ActionFactoryInternal::blessing_of_kings_on_party;
                creators["redemption"] = &ActionFactoryInternal::redemption;
                creators["crusader strike"] = &ActionFactoryInternal::crusader_strike;
                creators["crusader aura"] = &ActionFactoryInternal::crusader_aura;
                creators["seal of light"] = &ActionFactoryInternal::seal_of_light;
                creators["devotion aura"] = &ActionFactoryInternal::devotion_aura;
                creators["holy wrath"] = &ActionFactoryInternal::holy_wrath;
                creators["consecration"] = &ActionFactoryInternal::consecration;
                creators["cleanse"] = &ActionFactoryInternal::cleanse;
                creators["purify"] = &ActionFactoryInternal::purify;
                creators["cleanse poison on party"] = &ActionFactoryInternal::cleanse_poison_on_party;
                creators["cleanse disease on party"] = &ActionFactoryInternal::cleanse_disease_on_party;
                creators["cleanse magic on party"] = &ActionFactoryInternal::cleanse_magic_on_party;
                creators["purify poison on party"] = &ActionFactoryInternal::purify_poison_on_party;
                creators["purify disease on party"] = &ActionFactoryInternal::purify_disease_on_party;
                creators["seal of wisdom"] = &ActionFactoryInternal::seal_of_wisdom;
                creators["seal of justice"] = &ActionFactoryInternal::seal_of_justice;
                creators["seal of righteousness"] = &ActionFactoryInternal::seal_of_righteousness;
                creators["flash of light"] = &ActionFactoryInternal::flash_of_light;
                creators["hand of reckoning"] = &ActionFactoryInternal::hand_of_reckoning;
                creators["avenger's shield"] = &ActionFactoryInternal::avengers_shield;
                creators["exorcism"] = &ActionFactoryInternal::exorcism;
                creators["judgement of light"] = &ActionFactoryInternal::judgement_of_light;
                creators["judgement of wisdom"] = &ActionFactoryInternal::judgement_of_wisdom;
                creators["divine shield"] = &ActionFactoryInternal::divine_shield;
                creators["divine protection"] = &ActionFactoryInternal::divine_protection;
                creators["divine protection on party"] =&ActionFactoryInternal::divine_protection_on_party;
                creators["hammer of justice"] = &ActionFactoryInternal::hammer_of_justice;
                creators["flash of light on party"] = &ActionFactoryInternal::flash_of_light_on_party;
                creators["holy light"] = &ActionFactoryInternal::holy_light;
                creators["holy light on party"] = &ActionFactoryInternal::holy_light_on_party;
                creators["lay on hands"] = &ActionFactoryInternal::lay_on_hands;
                creators["lay on hands on party"] = &ActionFactoryInternal::lay_on_hands_on_party;
                creators["judgement of justice"] = &ActionFactoryInternal::judgement_of_justice;
                creators["hammer of wrath"] = &ActionFactoryInternal::hammer_of_wrath;
                creators["holy shield"] = &ActionFactoryInternal::holy_shield;
                creators["hammer of the righteous"] = &ActionFactoryInternal::hammer_of_the_righteous;
                creators["blessing of kings"] = &ActionFactoryInternal::blessing_of_kings;
                creators["retribution aura"] = &ActionFactoryInternal::retribution_aura;
                creators["shadow resistance aura"] = &ActionFactoryInternal::shadow_resistance_aura;
                creators["frost resistance aura"] = &ActionFactoryInternal::frost_resistance_aura;
                creators["fire resistance aura"] = &ActionFactoryInternal::fire_resistance_aura;
                creators["righteous fury"] = &ActionFactoryInternal::righteous_fury;
                creators["blessing of sanctuary"] = &ActionFactoryInternal::blessing_of_sanctuary;
            }

        private:
            Action* righteous_fury(AiManagerRegistry* ai) { return new CastRighteousFuryAction(ai); }
            Action* blessing_of_sanctuary(AiManagerRegistry* ai) { return new CastBlessingOfSanctuaryAction(ai); }
            Action* seal_of_command(AiManagerRegistry* ai) { return new CastSealOfCommandAction(ai); }
            Action* blessing_of_might(AiManagerRegistry* ai) { return new CastBlessingOfMightAction(ai); }
            Action* divine_storm(AiManagerRegistry* ai) { return new CastDivineStormAction(ai); }
            Action* blessing_of_kings_on_party(AiManagerRegistry* ai) { return new CastBlessingOfKingsOnPartyAction(ai); }
            Action* redemption(AiManagerRegistry* ai) { return new CastRedemptionAction(ai); }
            Action* crusader_strike(AiManagerRegistry* ai) { return new CastCrusaderStrikeAction(ai); }
            Action* crusader_aura(AiManagerRegistry* ai) { return new CastCrusaderAuraAction(ai); }
            Action* seal_of_light(AiManagerRegistry* ai) { return new CastSealOfLightAction(ai); }
            Action* devotion_aura(AiManagerRegistry* ai) { return new CastDevotionAuraAction(ai); }
            Action* holy_wrath(AiManagerRegistry* ai) { return new CastHolyWrathAction(ai); }
            Action* consecration(AiManagerRegistry* ai) { return new CastConsecrationAction(ai); }
            Action* cleanse(AiManagerRegistry* ai) { return new CastCleanseAction(ai); }
            Action* purify(AiManagerRegistry* ai) { return new CastPurifyAction(ai); }
            Action* cleanse_poison_on_party(AiManagerRegistry* ai) { return new CastCleansePoisonOnPartyAction(ai); }
            Action* cleanse_disease_on_party(AiManagerRegistry* ai) { return new CastCleanseDiseaseOnPartyAction(ai); }
            Action* cleanse_magic_on_party(AiManagerRegistry* ai) { return new CastCleanseMagicOnPartyAction(ai); }
            Action* purify_poison_on_party(AiManagerRegistry* ai) { return new CastPurifyPoisonOnPartyAction(ai); }
            Action* purify_disease_on_party(AiManagerRegistry* ai) { return new CastPurifyDiseaseOnPartyAction(ai); }
            Action* seal_of_wisdom(AiManagerRegistry* ai) { return new CastSealOfWisdomAction(ai); }
            Action* seal_of_justice(AiManagerRegistry* ai) { return new CastSealOfJusticeAction(ai); }
            Action* seal_of_righteousness(AiManagerRegistry* ai) { return new CastSealOfRighteousnessAction(ai); }
            Action* flash_of_light(AiManagerRegistry* ai) { return new CastFlashOfLightAction(ai); }
            Action* hand_of_reckoning(AiManagerRegistry* ai) { return new CastHandOfReckoningAction(ai); }
            Action* avengers_shield(AiManagerRegistry* ai) { return new CastAvengersShieldAction(ai); }
            Action* exorcism(AiManagerRegistry* ai) { return new CastExorcismAction(ai); }
            Action* judgement_of_light(AiManagerRegistry* ai) { return new CastJudgementOfLightAction(ai); }
            Action* judgement_of_wisdom(AiManagerRegistry* ai) { return new CastJudgementOfWisdomAction(ai); }
            Action* divine_shield(AiManagerRegistry* ai) { return new CastDivineShieldAction(ai); }
            Action* divine_protection(AiManagerRegistry* ai) { return new CastDivineProtectionAction(ai); }
            Action* divine_protection_on_party(AiManagerRegistry* ai) { return new CastDivineProtectionOnPartyAction(ai); }
            Action* hammer_of_justice(AiManagerRegistry* ai) { return new CastHammerOfJusticeAction(ai); }
            Action* flash_of_light_on_party(AiManagerRegistry* ai) { return new CastFlashOfLightOnPartyAction(ai); }
            Action* holy_light(AiManagerRegistry* ai) { return new CastHolyLightAction(ai); }
            Action* holy_light_on_party(AiManagerRegistry* ai) { return new CastHolyLightOnPartyAction(ai); }
            Action* lay_on_hands(AiManagerRegistry* ai) { return new CastLayOnHandsAction(ai); }
            Action* lay_on_hands_on_party(AiManagerRegistry* ai) { return new CastLayOnHandsOnPartyAction(ai); }
            Action* judgement_of_justice(AiManagerRegistry* ai) { return new CastJudgementOfJusticeAction(ai); }
            Action* hammer_of_wrath(AiManagerRegistry* ai) { return new CastHammerOfWrathAction(ai); }
            Action* holy_shield(AiManagerRegistry* ai) { return new CastHolyShieldAction(ai); }
            Action* hammer_of_the_righteous(AiManagerRegistry* ai) { return new CastHammerOfTheRighteousAction(ai); }
            Action* blessing_of_kings(AiManagerRegistry* ai) { return new CastBlessingOfKingsAction(ai); }
            Action* retribution_aura(AiManagerRegistry* ai) { return new CastRetributionAuraAction(ai); }
            Action* shadow_resistance_aura(AiManagerRegistry* ai) { return new CastShadowResistanceAuraAction(ai); }
            Action* frost_resistance_aura(AiManagerRegistry* ai) { return new CastFrostResistanceAuraAction(ai); }
            Action* fire_resistance_aura(AiManagerRegistry* ai) { return new CastFireResistanceAuraAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* PaladinActionFactory::createAction(const char* name)
{
    Action* action = ai::paladin::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
