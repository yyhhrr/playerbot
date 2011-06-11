#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidActions.h"
#include "DruidAiObjectContext.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "CasterDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"
#include "../NamedObjectContext.h"
#include "DruidTriggers.h"

using namespace ai;

namespace ai
{
    namespace druid
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["bear"] = &druid::StrategyFactoryInternal::bear;
                creators["tank"] = &druid::StrategyFactoryInternal::bear;

                creators["cat"] = &druid::StrategyFactoryInternal::cat;

                creators["caster"] = &druid::StrategyFactoryInternal::caster;
                creators["dps"] = &druid::StrategyFactoryInternal::caster;

                creators["nc"] = &druid::StrategyFactoryInternal::nc;
            }

        private:
            static Strategy* bear(AiManagerRegistry* ai) { return new BearTankDruidStrategy(ai); }
            static Strategy* cat(AiManagerRegistry* ai) { return new CatDpsDruidStrategy(ai); }
            static Strategy* caster(AiManagerRegistry* ai) { return new CasterDruidStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new GenericDruidNonCombatStrategy(ai); }
        };
    };
};

namespace ai
{
    namespace druid
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["thorns"] = &TriggerFactoryInternal::Thorns;
                creators["bash"] = &TriggerFactoryInternal::bash;
                creators["faerie fire (feral)"] = &TriggerFactoryInternal::faerie_fire_feral;
                creators["faerie fire"] = &TriggerFactoryInternal::faerie_fire;
                creators["insect swarm"] = &TriggerFactoryInternal::insect_swarm;
                creators["moonfire"] = &TriggerFactoryInternal::moonfire;
                creators["nature's grasp"] = &TriggerFactoryInternal::natures_grasp;
                creators["tiger's fury"] = &TriggerFactoryInternal::tigers_fury;
                creators["rake"] = &TriggerFactoryInternal::rake;
                creators["mark of the wild"] = &TriggerFactoryInternal::mark_of_the_wild;
                creators["mark of the wild on party"] = &TriggerFactoryInternal::mark_of_the_wild_on_party;
                creators["cure poison"] = &TriggerFactoryInternal::cure_poison;
                creators["party member cure poison"] = &TriggerFactoryInternal::party_member_cure_poison;
                creators["entangling roots"] = &TriggerFactoryInternal::entangling_roots;
            }

        private:
            static Trigger* Thorns(AiManagerRegistry* ai) { return new ThornsTrigger(ai); }
            static Trigger* bash(AiManagerRegistry* ai) { return new BashInterruptSpellTrigger(ai); }
            static Trigger* faerie_fire_feral(AiManagerRegistry* ai) { return new FaerieFireFeralTrigger(ai); }
            static Trigger* insect_swarm(AiManagerRegistry* ai) { return new InsectSwarmTrigger(ai); }
            static Trigger* moonfire(AiManagerRegistry* ai) { return new MoonfireTrigger(ai); }
            static Trigger* faerie_fire(AiManagerRegistry* ai) { return new FaerieFireTrigger(ai); }
            static Trigger* natures_grasp(AiManagerRegistry* ai) { return new NaturesGraspTrigger(ai); }
            static Trigger* tigers_fury(AiManagerRegistry* ai) { return new TigersFuryTrigger(ai); }
            static Trigger* rake(AiManagerRegistry* ai) { return new RakeTrigger(ai); }
            static Trigger* mark_of_the_wild(AiManagerRegistry* ai) { return new MarkOfTheWildTrigger(ai); }
            static Trigger* mark_of_the_wild_on_party(AiManagerRegistry* ai) { return new MarkOfTheWildOnPartyTrigger(ai); }
            static Trigger* cure_poison(AiManagerRegistry* ai) { return new CurePoisonTrigger(ai); }
            static Trigger* party_member_cure_poison(AiManagerRegistry* ai) { return new PartyMemberCurePoisonTrigger(ai); }
            static Trigger* entangling_roots(AiManagerRegistry* ai) { return new EntanglingRootsTrigger(ai); }
        };
    };
};

namespace ai
{
    namespace druid
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["feral charge - bear"] = &AiObjectContextInternal::feral_charge_bear;
                creators["feral charge - cat"] = &AiObjectContextInternal::feral_charge_cat;
                creators["swipe (bear)"] = &AiObjectContextInternal::swipe_bear;
                creators["faerie fire (feral)"] = &AiObjectContextInternal::faerie_fire_feral;
                creators["faerie fire"] = &AiObjectContextInternal::faerie_fire;
                creators["bear form"] = &AiObjectContextInternal::bear_form;
                creators["dire bear form"] = &AiObjectContextInternal::dire_bear_form;
                creators["moonkin form"] = &AiObjectContextInternal::moonkin_form;
                creators["cat form"] = &AiObjectContextInternal::cat_form;
                creators["caster form"] = &AiObjectContextInternal::caster_form;
                creators["mangle (bear)"] = &AiObjectContextInternal::mangle_bear;
                creators["maul"] = &AiObjectContextInternal::maul;
                creators["bash"] = &AiObjectContextInternal::bash;
                creators["swipe"] = &AiObjectContextInternal::swipe;
                creators["growl"] = &AiObjectContextInternal::growl;
                creators["demoralizing roar"] = &AiObjectContextInternal::demoralizing_roar;
                creators["hibernate"] = &AiObjectContextInternal::hibernate;
                creators["entangling roots"] = &AiObjectContextInternal::entangling_roots;
                creators["entangling roots on cc"] = &AiObjectContextInternal::entangling_roots_on_cc;
                creators["wrath"] = &AiObjectContextInternal::wrath;
                creators["starfall"] = &AiObjectContextInternal::starfall;
                creators["insect swarm"] = &AiObjectContextInternal::insect_swarm;
                creators["moonfire"] = &AiObjectContextInternal::moonfire;
                creators["starfire"] = &AiObjectContextInternal::starfire;
                creators["nature's grasp"] = &AiObjectContextInternal::natures_grasp;
                creators["claw"] = &AiObjectContextInternal::claw;
                creators["mangle (cat)"] = &AiObjectContextInternal::mangle_cat;
                creators["swipe (cat)"] = &AiObjectContextInternal::swipe_cat;
                creators["rake"] = &AiObjectContextInternal::rake;
                creators["ferocious bite"] = &AiObjectContextInternal::ferocious_bite;
                creators["rip"] = &AiObjectContextInternal::rip;
                creators["cower"] = &AiObjectContextInternal::cower;
                creators["survival instincts"] = &AiObjectContextInternal::survival_instincts;
                creators["thorns"] = &AiObjectContextInternal::thorns;
                creators["cure poison"] = &AiObjectContextInternal::cure_poison;
                creators["cure poison on party"] = &AiObjectContextInternal::cure_poison_on_party;
                creators["abolish poison"] = &AiObjectContextInternal::abolish_poison;
                creators["abolish poison on party"] = &AiObjectContextInternal::abolish_poison_on_party;
                creators["berserk"] = &AiObjectContextInternal::berserk;
                creators["tiger's fury"] = &AiObjectContextInternal::tigers_fury;
                creators["mark of the wild"] = &AiObjectContextInternal::mark_of_the_wild;
                creators["mark of the wild on party"] = &AiObjectContextInternal::mark_of_the_wild_on_party;
                creators["regrowth"] = &AiObjectContextInternal::regrowth;
                creators["rejuvenation"] = &AiObjectContextInternal::rejuvenation;
                creators["healing touch"] = &AiObjectContextInternal::healing_touch;
                creators["regrowth on party"] = &AiObjectContextInternal::regrowth_on_party;
                creators["rejuvenation on party"] = &AiObjectContextInternal::rejuvenation_on_party;
                creators["healing touch on party"] = &AiObjectContextInternal::healing_touch_on_party;
                creators["rebirth"] = &AiObjectContextInternal::rebirth;
                creators["revive"] = &AiObjectContextInternal::revive;
            }

        private:
            static Action* feral_charge_bear(AiManagerRegistry* ai) { return new CastFeralChargeBearAction(ai); }
            static Action* feral_charge_cat(AiManagerRegistry* ai) { return new CastFeralChargeCatAction(ai); }
            static Action* swipe_bear(AiManagerRegistry* ai) { return new CastSwipeBearAction(ai); }
            static Action* faerie_fire_feral(AiManagerRegistry* ai) { return new CastFaerieFireFeralAction(ai); }
            static Action* faerie_fire(AiManagerRegistry* ai) { return new CastFaerieFireAction(ai); }
            static Action* bear_form(AiManagerRegistry* ai) { return new CastBearFormAction(ai); }
            static Action* dire_bear_form(AiManagerRegistry* ai) { return new CastDireBearFormAction(ai); }
            static Action* cat_form(AiManagerRegistry* ai) { return new CastCatFormAction(ai); }
            static Action* caster_form(AiManagerRegistry* ai) { return new CastCasterFormAction(ai); }
            static Action* mangle_bear(AiManagerRegistry* ai) { return new CastMangleBearAction(ai); }
            static Action* maul(AiManagerRegistry* ai) { return new CastMaulAction(ai); }
            static Action* bash(AiManagerRegistry* ai) { return new CastBashAction(ai); }
            static Action* swipe(AiManagerRegistry* ai) { return new CastSwipeAction(ai); }
            static Action* growl(AiManagerRegistry* ai) { return new CastGrowlAction(ai); }
            static Action* demoralizing_roar(AiManagerRegistry* ai) { return new CastDemoralizingRoarAction(ai); }
            static Action* moonkin_form(AiManagerRegistry* ai) { return new CastMoonkinFormAction(ai); }
            static Action* hibernate(AiManagerRegistry* ai) { return new CastHibernateAction(ai); }
            static Action* entangling_roots(AiManagerRegistry* ai) { return new CastEntanglingRootsAction(ai); }
            static Action* entangling_roots_on_cc(AiManagerRegistry* ai) { return new CastEntanglingRootsCcAction(ai); }
            static Action* wrath(AiManagerRegistry* ai) { return new CastWrathAction(ai); }
            static Action* starfall(AiManagerRegistry* ai) { return new CastStarfallAction(ai); }
            static Action* insect_swarm(AiManagerRegistry* ai) { return new CastInsectSwarmAction(ai); }
            static Action* moonfire(AiManagerRegistry* ai) { return new CastMoonfireAction(ai); }
            static Action* starfire(AiManagerRegistry* ai) { return new CastStarfireAction(ai); }
            static Action* natures_grasp(AiManagerRegistry* ai) { return new CastNaturesGraspAction(ai); }
            static Action* claw(AiManagerRegistry* ai) { return new CastClawAction(ai); }
            static Action* mangle_cat(AiManagerRegistry* ai) { return new CastMangleCatAction(ai); }
            static Action* swipe_cat(AiManagerRegistry* ai) { return new CastSwipeCatAction(ai); }
            static Action* rake(AiManagerRegistry* ai) { return new CastRakeAction(ai); }
            static Action* ferocious_bite(AiManagerRegistry* ai) { return new CastFerociousBiteAction(ai); }
            static Action* rip(AiManagerRegistry* ai) { return new CastRipAction(ai); }
            static Action* cower(AiManagerRegistry* ai) { return new CastCowerAction(ai); }
            static Action* survival_instincts(AiManagerRegistry* ai) { return new CastSurvivalInstinctsAction(ai); }
            static Action* thorns(AiManagerRegistry* ai) { return new CastThornsAction(ai); }
            static Action* cure_poison(AiManagerRegistry* ai) { return new CastCurePoisonAction(ai); }
            static Action* cure_poison_on_party(AiManagerRegistry* ai) { return new CastCurePoisonOnPartyAction(ai); }
            static Action* abolish_poison(AiManagerRegistry* ai) { return new CastAbolishPoisonAction(ai); }
            static Action* abolish_poison_on_party(AiManagerRegistry* ai) { return new CastAbolishPoisonOnPartyAction(ai); }
            static Action* berserk(AiManagerRegistry* ai) { return new CastBerserkAction(ai); }
            static Action* tigers_fury(AiManagerRegistry* ai) { return new CastTigersFuryAction(ai); }
            static Action* mark_of_the_wild(AiManagerRegistry* ai) { return new CastMarkOfTheWildAction(ai); }
            static Action* mark_of_the_wild_on_party(AiManagerRegistry* ai) { return new CastMarkOfTheWildOnPartyAction(ai); }
            static Action* regrowth(AiManagerRegistry* ai) { return new CastRegrowthAction(ai); }
            static Action* rejuvenation(AiManagerRegistry* ai) { return new CastRejuvenationAction(ai); }
            static Action* healing_touch(AiManagerRegistry* ai) { return new CastHealingTouchAction(ai); }
            static Action* regrowth_on_party(AiManagerRegistry* ai) { return new CastRegrowthOnPartyAction(ai); }
            static Action* rejuvenation_on_party(AiManagerRegistry* ai) { return new CastRejuvenationOnPartyAction(ai); }
            static Action* healing_touch_on_party(AiManagerRegistry* ai) { return new CastHealingTouchOnPartyAction(ai); }
            static Action* rebirth(AiManagerRegistry* ai) { return new CastRebirthAction(ai); }
            static Action* revive(AiManagerRegistry* ai) { return new CastReviveAction(ai); }
        };
    };
};

DruidAiObjectContext::DruidAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::druid::StrategyFactoryInternal());
    actionContexts.Add(new ai::druid::AiObjectContextInternal());
    triggerContexts.Add(new ai::druid::TriggerFactoryInternal());    
}