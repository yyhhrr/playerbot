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

        class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
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
            static Strategy* tank(AiManagerRegistry* ai) { return new TankWarlockStrategy(ai); }
            static Strategy* dps(AiManagerRegistry* ai) { return new DpsWarlockStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new GenericWarlockNonCombatStrategy(ai); }
            static Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        };
    };
};

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
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
            static Trigger* shadow_trance(AiManagerRegistry* ai) { return new ShadowTranceTrigger(ai); }
            static Trigger* demon_armor(AiManagerRegistry* ai) { return new DemonArmorTrigger(ai); }
            static Trigger* HasHealthstone(AiManagerRegistry* ai) { return new HasHealthstoneTrigger(ai); }
            static Trigger* HasFirestone(AiManagerRegistry* ai) { return new HasFirestoneTrigger(ai); }
            static Trigger* HasSpellstone(AiManagerRegistry* ai) { return new HasSpellstoneTrigger(ai); }
            static Trigger* corruption(AiManagerRegistry* ai) { return new CorruptionTrigger(ai); }
            static Trigger* curse_of_agony(AiManagerRegistry* ai) { return new CurseOfAgonyTrigger(ai); }
            static Trigger* banish(AiManagerRegistry* ai) { return new BanishTrigger(ai); }
            static Trigger* spellstone(AiManagerRegistry* ai) { return new SpellstoneTrigger(ai); }

        };
    };
};

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        class ActionFactoryInternal : public NamedObjectFactory<Action>
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
            static Action* immolate(AiManagerRegistry* ai) { return new CastImmolateAction(ai); }
            static Action* summon_imp(AiManagerRegistry* ai) { return new CastSummonImpAction(ai); }
            static Action* demon_armor(AiManagerRegistry* ai) { return new CastDemonArmorAction(ai); }
            static Action* demon_skin(AiManagerRegistry* ai) { return new CastDemonSkinAction(ai); }
            static Action* create_healthstone(AiManagerRegistry* ai) { return new CastCreateHealthstoneAction(ai); }
            static Action* create_firestone(AiManagerRegistry* ai) { return new CastCreateFirestoneAction(ai); }
            static Action* create_spellstone(AiManagerRegistry* ai) { return new CastCreateSpellstoneAction(ai); }
            static Action* spellstone(AiManagerRegistry* ai) { return new UseItemAction(ai, "spellstone"); }
            static Action* summon_voidwalker(AiManagerRegistry* ai) { return new CastSummonVoidwalkerAction(ai); }
            static Action* corruption(AiManagerRegistry* ai) { return new CastCorruptionAction(ai); }
            static Action* curse_of_agony(AiManagerRegistry* ai) { return new CastCurseOfAgonyAction(ai); }
            static Action* shadow_bolt(AiManagerRegistry* ai) { return new CastShadowBoltAction(ai); }
            static Action* drain_soul(AiManagerRegistry* ai) { return new CastDrainSoulAction(ai); }
            static Action* drain_mana(AiManagerRegistry* ai) { return new CastDrainManaAction(ai); }
            static Action* drain_life(AiManagerRegistry* ai) { return new CastDrainLifeAction(ai); }
            static Action* banish(AiManagerRegistry* ai) { return new CastBanishAction(ai); }

        };
    };
};



WarlockActionFactory::WarlockActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai)
{
    strategyFactories.push_back(new ai::warlock::StrategyFactoryInternal());
    actionFactories.push_back(new ai::warlock::ActionFactoryInternal());
    triggerFactories.push_back(new ai::warlock::TriggerFactoryInternal());    
}