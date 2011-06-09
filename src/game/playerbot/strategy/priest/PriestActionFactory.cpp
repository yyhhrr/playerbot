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

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, priest::StrategyFactoryInternal>
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
            Strategy* heal(AiManagerRegistry* ai) { return new HealPriestStrategy(ai); }
            Strategy* dps(AiManagerRegistry* ai) { return new DpsPriestStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new HealPriestNonCombatStrategy(ai); }
            Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        }
        strategyFactoryInternal;
    };
};

Strategy* PriestActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::priest::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace priest
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
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
            Trigger* devouring_plague(AiManagerRegistry* ai) { return new DevouringPlagueTrigger(ai); }
            Trigger* shadow_word_pain(AiManagerRegistry* ai) { return new PowerWordPainTrigger(ai); }
            Trigger* dispel_magic(AiManagerRegistry* ai) { return new DispelMagicTrigger(ai); }
            Trigger* dispel_magic_party_member(AiManagerRegistry* ai) { return new DispelMagicPartyMemberTrigger(ai); }
            Trigger* cure_disease(AiManagerRegistry* ai) { return new CureDiseaseTrigger(ai); }
            Trigger* party_member_cure_disease(AiManagerRegistry* ai) { return new PartyMemberCureDiseaseTrigger(ai); }
            Trigger* power_word_fortitude(AiManagerRegistry* ai) { return new PowerWordFortitudeTrigger(ai); }
            Trigger* power_word_fortitude_on_party(AiManagerRegistry* ai) { return new PowerWordFortitudeOnPartyTrigger(ai); }
            Trigger* divine_spirit(AiManagerRegistry* ai) { return new DivineSpiritTrigger(ai); }
            Trigger* divine_spirit_on_party(AiManagerRegistry* ai) { return new DivineSpiritOnPartyTrigger(ai); }
            Trigger* inner_fire(AiManagerRegistry* ai) { return new InnerFireTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* PriestActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::priest::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace priest
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
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
            Action* resurrection(AiManagerRegistry* ai) { return new CastResurrectionAction(ai); }
            Action* shadow_word_pain(AiManagerRegistry* ai) { return new CastPowerWordPainAction(ai); }
            Action* devouring_plague(AiManagerRegistry* ai) { return new CastDevouringPlagueAction(ai); }
            Action* mind_flay(AiManagerRegistry* ai) { return new CastMindFlayAction(ai); }
            Action* holy_fire(AiManagerRegistry* ai) { return new CastHolyFireAction(ai); }
            Action* smite(AiManagerRegistry* ai) { return new CastSmiteAction(ai); }
            Action* mind_blast(AiManagerRegistry* ai) { return new CastMindBlastAction(ai); }
            Action* shadowform(AiManagerRegistry* ai) { return new CastShadowformAction(ai); }
            Action* remove_shadowform(AiManagerRegistry* ai) { return new CastRemoveShadowformAction(ai); }
            Action* holy_nova(AiManagerRegistry* ai) { return new CastHolyNovaAction(ai); }
            Action* power_word_fortitude(AiManagerRegistry* ai) { return new CastPowerWordFortitudeAction(ai); }
            Action* power_word_fortitude_on_party(AiManagerRegistry* ai) { return new CastPowerWordFortitudeOnPartyAction(ai); }
            Action* divine_spirit(AiManagerRegistry* ai) { return new CastDivineSpiritAction(ai); }
            Action* divine_spirit_on_party(AiManagerRegistry* ai) { return new CastDivineSpiritOnPartyAction(ai); }
            Action* power_word_shield(AiManagerRegistry* ai) { return new CastPowerWordShieldAction(ai); }
            Action* power_word_shield_on_party(AiManagerRegistry* ai) { return new CastPowerWordShieldOnPartyAction(ai); }
            Action* renew(AiManagerRegistry* ai) { return new CastRenewAction(ai); }
            Action* renew_on_party(AiManagerRegistry* ai) { return new CastRenewOnPartyAction(ai); }
            Action* greater_heal(AiManagerRegistry* ai) { return new CastGreaterHealAction(ai); }
            Action* greater_heal_on_party(AiManagerRegistry* ai) { return new CastGreaterHealOnPartyAction(ai); }
            Action* heal(AiManagerRegistry* ai) { return new CastHealAction(ai); }
            Action* heal_on_party(AiManagerRegistry* ai) { return new CastHealOnPartyAction(ai); }
            Action* lesser_heal(AiManagerRegistry* ai) { return new CastLesserHealAction(ai); }
            Action* lesser_heal_on_party(AiManagerRegistry* ai) { return new CastLesserHealOnPartyAction(ai); }
            Action* flash_heal(AiManagerRegistry* ai) { return new CastFlashHealAction(ai); }
            Action* flash_heal_on_party(AiManagerRegistry* ai) { return new CastFlashHealOnPartyAction(ai); }
            Action* dispel_magic(AiManagerRegistry* ai) { return new CastDispelMagicAction(ai); }
            Action* dispel_magic_on_party(AiManagerRegistry* ai) { return new CastDispelMagicOnPartyAction(ai); }
            Action* dispel_magic_on_target(AiManagerRegistry* ai) { return new CastDispelMagicOnTargetAction(ai); }
            Action* cure_disease(AiManagerRegistry* ai) { return new CastCureDiseaseAction(ai); }
            Action* cure_disease_on_party(AiManagerRegistry* ai) { return new CastCureDiseaseOnPartyAction(ai); }
            Action* abolish_disease(AiManagerRegistry* ai) { return new CastAbolishDiseaseAction(ai); }
            Action* abolish_disease_on_party(AiManagerRegistry* ai) { return new CastAbolishDiseaseOnPartyAction(ai); }
            Action* fade(AiManagerRegistry* ai) { return new CastFadeAction(ai); }
            Action* inner_fire(AiManagerRegistry* ai) { return new CastInnerFireAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* PriestActionFactory::createAction(const char* name)
{
    Action* action = ai::priest::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
