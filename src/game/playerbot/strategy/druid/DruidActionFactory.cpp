#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "CasterDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"
#include "../NamedObjectFactory.h"
#include "DruidTriggers.h"

using namespace ai;

namespace ai
{
    namespace druid
    {
        using namespace ai;

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, druid::StrategyFactoryInternal>
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
            Strategy* bear(AiManagerRegistry* ai) { return new BearTankDruidStrategy(ai); }
            Strategy* cat(AiManagerRegistry* ai) { return new CatDpsDruidStrategy(ai); }
            Strategy* caster(AiManagerRegistry* ai) { return new CasterDruidStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericDruidNonCombatStrategy(ai); }
        }
        strategyFactoryInternal;
    };
};

Strategy* DruidActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::druid::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace druid
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
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
            }

        private:
            Trigger* Thorns(AiManagerRegistry* ai) { return new ThornsTrigger(ai); }
            Trigger* bash(AiManagerRegistry* ai) { return new BashInterruptSpellTrigger(ai); }
            Trigger* faerie_fire_feral(AiManagerRegistry* ai) { return new FaerieFireFeralTrigger(ai); }
            Trigger* insect_swarm(AiManagerRegistry* ai) { return new InsectSwarmTrigger(ai); }
            Trigger* moonfire(AiManagerRegistry* ai) { return new MoonfireTrigger(ai); }
            Trigger* faerie_fire(AiManagerRegistry* ai) { return new FaerieFireTrigger(ai); }
            Trigger* natures_grasp(AiManagerRegistry* ai) { return new NaturesGraspTrigger(ai); }
            Trigger* tigers_fury(AiManagerRegistry* ai) { return new TigersFuryTrigger(ai); }
            Trigger* rake(AiManagerRegistry* ai) { return new RakeTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* DruidActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::druid::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace druid
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
        {
        public:
            ActionFactoryInternal()
            {
                creators["feral charge - bear"] = &ActionFactoryInternal::feral_charge_bear;
                creators["swipe (bear)"] = &ActionFactoryInternal::swipe_bear;
                creators["faerie fire (feral)"] = &ActionFactoryInternal::faerie_fire_feral;
                creators["faerie fire"] = &ActionFactoryInternal::faerie_fire;
                creators["bear form"] = &ActionFactoryInternal::bear_form;
                creators["dire bear form"] = &ActionFactoryInternal::dire_bear_form;
                creators["mangle (bear)"] = &ActionFactoryInternal::mangle_bear;
                creators["maul"] = &ActionFactoryInternal::maul;
                creators["bash"] = &ActionFactoryInternal::bash;
                creators["swipe"] = &ActionFactoryInternal::swipe;
                creators["growl"] = &ActionFactoryInternal::growl;
                creators["demoralizing roar"] = &ActionFactoryInternal::demoralizing_roar;
                creators["moonkin form"] = &ActionFactoryInternal::moonkin_form;
                creators["hibernate"] = &ActionFactoryInternal::hibernate;
                creators["entangling roots"] = &ActionFactoryInternal::entangling_roots;
                creators["entangling roots on cc"] = &ActionFactoryInternal::entangling_roots_on_cc;
                creators["wrath"] = &ActionFactoryInternal::wrath;
                creators["starfall"] = &ActionFactoryInternal::starfall;
                creators["insect swarm"] = &ActionFactoryInternal::insect_swarm;
                creators["moonfire"] = &ActionFactoryInternal::moonfire;
                creators["starfire"] = &ActionFactoryInternal::starfire;
                creators["nature's grasp"] = &ActionFactoryInternal::natures_grasp;
            }

        private:
            Action* feral_charge_bear(AiManagerRegistry* ai) { return new CastFeralChargeBearAction(ai); }
            Action* swipe_bear(AiManagerRegistry* ai) { return new CastSwipeBearAction(ai); }
            Action* faerie_fire_feral(AiManagerRegistry* ai) { return new CastFaerieFireFeralAction(ai); }
            Action* faerie_fire(AiManagerRegistry* ai) { return new CastFaerieFireAction(ai); }
            Action* bear_form(AiManagerRegistry* ai) { return new CastBearFormAction(ai); }
            Action* dire_bear_form(AiManagerRegistry* ai) { return new CastDireBearFormAction(ai); }
            Action* mangle_bear(AiManagerRegistry* ai) { return new CastMangleBearAction(ai); }
            Action* maul(AiManagerRegistry* ai) { return new CastMaulAction(ai); }
            Action* bash(AiManagerRegistry* ai) { return new CastBashAction(ai); }
            Action* swipe(AiManagerRegistry* ai) { return new CastSwipeAction(ai); }
            Action* growl(AiManagerRegistry* ai) { return new CastGrowlAction(ai); }
            Action* demoralizing_roar(AiManagerRegistry* ai) { return new CastDemoralizingRoarAction(ai); }
            Action* moonkin_form(AiManagerRegistry* ai) { return new CastMoonkinFormAction(ai); }
            Action* hibernate(AiManagerRegistry* ai) { return new CastHibernateAction(ai); }
            Action* entangling_roots(AiManagerRegistry* ai) { return new CastEntanglingRootsAction(ai); }
            Action* entangling_roots_on_cc(AiManagerRegistry* ai) { return new CastEntanglingRootsCcAction(ai); }
            Action* wrath(AiManagerRegistry* ai) { return new CastWrathAction(ai); }
            Action* starfall(AiManagerRegistry* ai) { return new CastStarfallAction(ai); }
            Action* insect_swarm(AiManagerRegistry* ai) { return new CastInsectSwarmAction(ai); }
            Action* moonfire(AiManagerRegistry* ai) { return new CastMoonfireAction(ai); }
            Action* starfire(AiManagerRegistry* ai) { return new CastStarfireAction(ai); }
            Action* natures_grasp(AiManagerRegistry* ai) { return new CastNaturesGraspAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* DruidActionFactory::createAction(const char* name)
{
    Action* action = ai::druid::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
