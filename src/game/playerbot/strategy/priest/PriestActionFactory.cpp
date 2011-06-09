#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestActions.h"
#include "PriestActionFactory.h"
#include "HealPriestNonCombatStrategy.h"
#include "DpsPriestStrategy.h"
#include "../PullStrategy.h"
#include "PriestTriggers.h"
#include "../NamedObjectFactory.h"

using namespace ai;


namespace ai
{
    namespace priest
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["heal"] = &priest::StrategyFactoryInternal::heal;
                creators["dps"] = &priest::StrategyFactoryInternal::dps;
                creators["nc"] = &priest::StrategyFactoryInternal::nc;
                creators["pull"] = &priest::StrategyFactoryInternal::pull;
            }

        private:
            static Strategy* heal(AiManagerRegistry* ai) { return new HealPriestStrategy(ai); }
            static Strategy* dps(AiManagerRegistry* ai) { return new DpsPriestStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new HealPriestNonCombatStrategy(ai); }
            static Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        };
    };
};

namespace ai
{
    namespace priest
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["devouring plague"] = &TriggerFactoryInternal::devouring_plague;
                creators["shadow word: pain"] = &TriggerFactoryInternal::shadow_word_pain;
                creators["dispel magic"] = &TriggerFactoryInternal::dispel_magic;
                creators["dispel magic on party"] = &TriggerFactoryInternal::dispel_magic_party_member;
                creators["cure disease"] = &TriggerFactoryInternal::cure_disease;
                creators["party member cure disease"] = &TriggerFactoryInternal::party_member_cure_disease;
                creators["power word: fortitude"] = &TriggerFactoryInternal::power_word_fortitude;
                creators["power word: fortitude on party"] = &TriggerFactoryInternal::power_word_fortitude_on_party;
                creators["divine spirit"] = &TriggerFactoryInternal::divine_spirit;
                creators["divine spirit on party"] = &TriggerFactoryInternal::divine_spirit_on_party;
                creators["inner fire"] = &TriggerFactoryInternal::inner_fire;

            }

        private:
            static Trigger* devouring_plague(AiManagerRegistry* ai) { return new DevouringPlagueTrigger(ai); }
            static Trigger* shadow_word_pain(AiManagerRegistry* ai) { return new PowerWordPainTrigger(ai); }
            static Trigger* dispel_magic(AiManagerRegistry* ai) { return new DispelMagicTrigger(ai); }
            static Trigger* dispel_magic_party_member(AiManagerRegistry* ai) { return new DispelMagicPartyMemberTrigger(ai); }
            static Trigger* cure_disease(AiManagerRegistry* ai) { return new CureDiseaseTrigger(ai); }
            static Trigger* party_member_cure_disease(AiManagerRegistry* ai) { return new PartyMemberCureDiseaseTrigger(ai); }
            static Trigger* power_word_fortitude(AiManagerRegistry* ai) { return new PowerWordFortitudeTrigger(ai); }
            static Trigger* power_word_fortitude_on_party(AiManagerRegistry* ai) { return new PowerWordFortitudeOnPartyTrigger(ai); }
            static Trigger* divine_spirit(AiManagerRegistry* ai) { return new DivineSpiritTrigger(ai); }
            static Trigger* divine_spirit_on_party(AiManagerRegistry* ai) { return new DivineSpiritOnPartyTrigger(ai); }
            static Trigger* inner_fire(AiManagerRegistry* ai) { return new InnerFireTrigger(ai); }
        };
    };
};



namespace ai
{
    namespace priest
    {
        using namespace ai;

        class ActionFactoryInternal : public NamedObjectFactory<Action>
        {
        public:
            ActionFactoryInternal()
            {
                creators["shadow word: pain"] = &ActionFactoryInternal::shadow_word_pain;
                creators["devouring plague"] = &ActionFactoryInternal::devouring_plague;
                creators["mind flay"] = &ActionFactoryInternal::mind_flay;
                creators["holy fire"] = &ActionFactoryInternal::holy_fire;
                creators["smite"] = &ActionFactoryInternal::smite;
                creators["mind blast"] = &ActionFactoryInternal::mind_blast;
                creators["shadowform"] = &ActionFactoryInternal::shadowform;
                creators["remove shadowform"] = &ActionFactoryInternal::remove_shadowform;
                creators["holy nova"] = &ActionFactoryInternal::holy_nova;
                creators["power word: fortitude"] = &ActionFactoryInternal::power_word_fortitude;
                creators["power word: fortitude on party"] = &ActionFactoryInternal::power_word_fortitude_on_party;
                creators["divine spirit"] = &ActionFactoryInternal::divine_spirit;
                creators["divine spirit on party"] = &ActionFactoryInternal::divine_spirit_on_party;
                creators["power word: shield"] = &ActionFactoryInternal::power_word_shield;
                creators["power word: shield on party"] = &ActionFactoryInternal::power_word_shield_on_party;
                creators["renew"] = &ActionFactoryInternal::renew;
                creators["renew on party"] = &ActionFactoryInternal::renew_on_party;
                creators["greater heal"] = &ActionFactoryInternal::greater_heal;
                creators["greater heal on party"] = &ActionFactoryInternal::greater_heal_on_party;
                creators["heal"] = &ActionFactoryInternal::heal;
                creators["heal on party"] = &ActionFactoryInternal::heal_on_party;
                creators["lesser heal"] = &ActionFactoryInternal::lesser_heal;
                creators["lesser heal on party"] = &ActionFactoryInternal::lesser_heal_on_party;
                creators["flash heal"] = &ActionFactoryInternal::flash_heal;
                creators["flash heal on party"] = &ActionFactoryInternal::flash_heal_on_party;
                creators["dispel magic"] = &ActionFactoryInternal::dispel_magic;
                creators["dispel magic on party"] = &ActionFactoryInternal::dispel_magic_on_party;
                creators["dispel magic on target"] = &ActionFactoryInternal::dispel_magic_on_target;
                creators["cure disease"] = &ActionFactoryInternal::cure_disease;
                creators["cure disease on party"] = &ActionFactoryInternal::cure_disease_on_party;
                creators["abolish disease"] = &ActionFactoryInternal::abolish_disease;
                creators["abolish disease on party"] = &ActionFactoryInternal::abolish_disease_on_party;
                creators["fade"] = &ActionFactoryInternal::fade;
                creators["inner fire"] = &ActionFactoryInternal::inner_fire;
                creators["resurrection"] = &ActionFactoryInternal::resurrection;
            }

        private:
            static Action* resurrection(AiManagerRegistry* ai) { return new CastResurrectionAction(ai); }
            static Action* shadow_word_pain(AiManagerRegistry* ai) { return new CastPowerWordPainAction(ai); }
            static Action* devouring_plague(AiManagerRegistry* ai) { return new CastDevouringPlagueAction(ai); }
            static Action* mind_flay(AiManagerRegistry* ai) { return new CastMindFlayAction(ai); }
            static Action* holy_fire(AiManagerRegistry* ai) { return new CastHolyFireAction(ai); }
            static Action* smite(AiManagerRegistry* ai) { return new CastSmiteAction(ai); }
            static Action* mind_blast(AiManagerRegistry* ai) { return new CastMindBlastAction(ai); }
            static Action* shadowform(AiManagerRegistry* ai) { return new CastShadowformAction(ai); }
            static Action* remove_shadowform(AiManagerRegistry* ai) { return new CastRemoveShadowformAction(ai); }
            static Action* holy_nova(AiManagerRegistry* ai) { return new CastHolyNovaAction(ai); }
            static Action* power_word_fortitude(AiManagerRegistry* ai) { return new CastPowerWordFortitudeAction(ai); }
            static Action* power_word_fortitude_on_party(AiManagerRegistry* ai) { return new CastPowerWordFortitudeOnPartyAction(ai); }
            static Action* divine_spirit(AiManagerRegistry* ai) { return new CastDivineSpiritAction(ai); }
            static Action* divine_spirit_on_party(AiManagerRegistry* ai) { return new CastDivineSpiritOnPartyAction(ai); }
            static Action* power_word_shield(AiManagerRegistry* ai) { return new CastPowerWordShieldAction(ai); }
            static Action* power_word_shield_on_party(AiManagerRegistry* ai) { return new CastPowerWordShieldOnPartyAction(ai); }
            static Action* renew(AiManagerRegistry* ai) { return new CastRenewAction(ai); }
            static Action* renew_on_party(AiManagerRegistry* ai) { return new CastRenewOnPartyAction(ai); }
            static Action* greater_heal(AiManagerRegistry* ai) { return new CastGreaterHealAction(ai); }
            static Action* greater_heal_on_party(AiManagerRegistry* ai) { return new CastGreaterHealOnPartyAction(ai); }
            static Action* heal(AiManagerRegistry* ai) { return new CastHealAction(ai); }
            static Action* heal_on_party(AiManagerRegistry* ai) { return new CastHealOnPartyAction(ai); }
            static Action* lesser_heal(AiManagerRegistry* ai) { return new CastLesserHealAction(ai); }
            static Action* lesser_heal_on_party(AiManagerRegistry* ai) { return new CastLesserHealOnPartyAction(ai); }
            static Action* flash_heal(AiManagerRegistry* ai) { return new CastFlashHealAction(ai); }
            static Action* flash_heal_on_party(AiManagerRegistry* ai) { return new CastFlashHealOnPartyAction(ai); }
            static Action* dispel_magic(AiManagerRegistry* ai) { return new CastDispelMagicAction(ai); }
            static Action* dispel_magic_on_party(AiManagerRegistry* ai) { return new CastDispelMagicOnPartyAction(ai); }
            static Action* dispel_magic_on_target(AiManagerRegistry* ai) { return new CastDispelMagicOnTargetAction(ai); }
            static Action* cure_disease(AiManagerRegistry* ai) { return new CastCureDiseaseAction(ai); }
            static Action* cure_disease_on_party(AiManagerRegistry* ai) { return new CastCureDiseaseOnPartyAction(ai); }
            static Action* abolish_disease(AiManagerRegistry* ai) { return new CastAbolishDiseaseAction(ai); }
            static Action* abolish_disease_on_party(AiManagerRegistry* ai) { return new CastAbolishDiseaseOnPartyAction(ai); }
            static Action* fade(AiManagerRegistry* ai) { return new CastFadeAction(ai); }
            static Action* inner_fire(AiManagerRegistry* ai) { return new CastInnerFireAction(ai); }
        };
    };
};

PriestActionFactory::PriestActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai)
{
    strategyFactories.push_back(new ai::priest::StrategyFactoryInternal());
    actionFactories.push_back(new ai::priest::ActionFactoryInternal());
    triggerFactories.push_back(new ai::priest::TriggerFactoryInternal());    
}