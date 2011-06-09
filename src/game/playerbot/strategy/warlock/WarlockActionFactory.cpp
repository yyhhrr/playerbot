#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockActions.h"
#include "WarlockActionFactory.h"
#include "DpsWarlockStrategy.h"
#include "GenericWarlockNonCombatStrategy.h"
#include "TankWarlockStrategy.h"
#include "../PullStrategy.h"
#include "WarlockTriggers.h"
#include "../NamedObjectFactory.h"

using namespace ai;

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, warlock::StrategyFactoryInternal>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &warlock::StrategyFactoryInternal::dps;
                creators["tank"] = &warlock::StrategyFactoryInternal::tank;
                creators["nc"] = &warlock::StrategyFactoryInternal::nc;
                creators["pull"] = &warlock::StrategyFactoryInternal::pull;
            }

        private:
            Strategy* tank(AiManagerRegistry* ai) { return new TankWarlockStrategy(ai); }
            Strategy* dps(AiManagerRegistry* ai) { return new DpsWarlockStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericWarlockNonCombatStrategy(ai); }
            Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        }
        strategyFactoryInternal;
    };
};

Strategy* WarlockActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::warlock::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["shadow trance"] = &TriggerFactoryInternal::shadow_trance;
                creators["demon armor"] = &TriggerFactoryInternal::demon_armor;
                creators["no healthstone"] = &TriggerFactoryInternal::HasHealthstone;
                creators["no firestone"] = &TriggerFactoryInternal::HasFirestone;
                creators["no spellstone"] = &TriggerFactoryInternal::HasSpellstone;
                creators["corruption"] = &TriggerFactoryInternal::corruption;
                creators["curse of agony"] = &TriggerFactoryInternal::curse_of_agony;
                creators["banish"] = &TriggerFactoryInternal::banish;
                creators["spellstone"] = &TriggerFactoryInternal::spellstone;


            }

        private:
            Trigger* shadow_trance(AiManagerRegistry* ai) { return new ShadowTranceTrigger(ai); }
            Trigger* demon_armor(AiManagerRegistry* ai) { return new DemonArmorTrigger(ai); }
            Trigger* HasHealthstone(AiManagerRegistry* ai) { return new HasHealthstoneTrigger(ai); }
            Trigger* HasFirestone(AiManagerRegistry* ai) { return new HasFirestoneTrigger(ai); }
            Trigger* HasSpellstone(AiManagerRegistry* ai) { return new HasSpellstoneTrigger(ai); }
            Trigger* corruption(AiManagerRegistry* ai) { return new CorruptionTrigger(ai); }
            Trigger* curse_of_agony(AiManagerRegistry* ai) { return new CurseOfAgonyTrigger(ai); }
            Trigger* banish(AiManagerRegistry* ai) { return new BanishTrigger(ai); }
            Trigger* spellstone(AiManagerRegistry* ai) { return new SpellstoneTrigger(ai); }

        }
        triggerFactoryInternal;
    };
};

Trigger* WarlockActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::warlock::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace warlock
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
        {
        public:
            ActionFactoryInternal()
            {
                creators["summon imp"] = &ActionFactoryInternal::summon_imp;
                creators["demon armor"] = &ActionFactoryInternal::demon_armor;
                creators["demon skin"] = &ActionFactoryInternal::demon_skin;
                creators["create healthstone"] = &ActionFactoryInternal::create_healthstone;
                creators["create firestone"] = &ActionFactoryInternal::create_firestone;
                creators["create spellstone"] = &ActionFactoryInternal::create_spellstone;
                creators["spellstone"] = &ActionFactoryInternal::spellstone;
                creators["summon voidwalker"] = &ActionFactoryInternal::summon_voidwalker;
                creators["immolate"] = &ActionFactoryInternal::immolate;
                creators["corruption"] = &ActionFactoryInternal::corruption;
                creators["curse of agony"] = &ActionFactoryInternal::curse_of_agony;
                creators["shadow bolt"] = &ActionFactoryInternal::shadow_bolt;
                creators["drain soul"] = &ActionFactoryInternal::drain_soul;
                creators["drain mana"] = &ActionFactoryInternal::drain_mana;
                creators["drain life"] = &ActionFactoryInternal::drain_life;
                creators["banish"] = &ActionFactoryInternal::banish;
            }

        private:
            Action* immolate(AiManagerRegistry* ai) { return new CastImmolateAction(ai); }
            Action* summon_imp(AiManagerRegistry* ai) { return new CastSummonImpAction(ai); }
            Action* demon_armor(AiManagerRegistry* ai) { return new CastDemonArmorAction(ai); }
            Action* demon_skin(AiManagerRegistry* ai) { return new CastDemonSkinAction(ai); }
            Action* create_healthstone(AiManagerRegistry* ai) { return new CastCreateHealthstoneAction(ai); }
            Action* create_firestone(AiManagerRegistry* ai) { return new CastCreateFirestoneAction(ai); }
            Action* create_spellstone(AiManagerRegistry* ai) { return new CastCreateSpellstoneAction(ai); }
            Action* spellstone(AiManagerRegistry* ai) { return new UseItemAction(ai, "spellstone"); }
            Action* summon_voidwalker(AiManagerRegistry* ai) { return new CastSummonVoidwalkerAction(ai); }
            Action* corruption(AiManagerRegistry* ai) { return new CastCorruptionAction(ai); }
            Action* curse_of_agony(AiManagerRegistry* ai) { return new CastCurseOfAgonyAction(ai); }
            Action* shadow_bolt(AiManagerRegistry* ai) { return new CastShadowBoltAction(ai); }
            Action* drain_soul(AiManagerRegistry* ai) { return new CastDrainSoulAction(ai); }
            Action* drain_mana(AiManagerRegistry* ai) { return new CastDrainManaAction(ai); }
            Action* drain_life(AiManagerRegistry* ai) { return new CastDrainLifeAction(ai); }
            Action* banish(AiManagerRegistry* ai) { return new CastBanishAction(ai); }

        }
        actionFactoryInternal;
    };
};

Action* WarlockActionFactory::createAction(const char* name)
{
    Action* action = ai::warlock::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
