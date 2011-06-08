#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterActions.h"
#include "HunterTriggers.h"
#include "HunterActionFactory.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterBuffStrategies.h"
#include "../NamedObjectFactory.h"

using namespace ai;


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, hunter::StrategyFactoryInternal>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &hunter::StrategyFactoryInternal::dps;
                creators["nc"] = &hunter::StrategyFactoryInternal::nc;
                creators["bspeed"] = &hunter::StrategyFactoryInternal::bspeed;
                creators["bdps"] = &hunter::StrategyFactoryInternal::bdps;
                creators["rnature"] = &hunter::StrategyFactoryInternal::rnature;
            }

        private:
            Strategy* dps(AiManagerRegistry* ai) { return new DpsHunterStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericHunterNonCombatStrategy(ai); }
            Strategy* bspeed(AiManagerRegistry* ai) { return new HunterBuffSpeedNonCombatStrategy(ai); }
            Strategy* bdps(AiManagerRegistry* ai) { return new HunterBuffDpsStrategy(ai); }
            Strategy* rnature(AiManagerRegistry* ai) { return new HunterNatureResistanceStrategy(ai); }
        }
        strategyFactoryInternal;
    };
};

Strategy* HunterActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::hunter::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace hunter
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["aspect of the viper"] = &TriggerFactoryInternal::aspect_of_the_viper;
                creators["black arrow"] = &TriggerFactoryInternal::black_arrow;
                creators["no stings"] = &TriggerFactoryInternal::NoStings;
                creators["hunters pet dead"] = &TriggerFactoryInternal::hunters_pet_dead;
                creators["hunters pet low health"] = &TriggerFactoryInternal::hunters_pet_low_health;
                creators["hunter's mark"] = &TriggerFactoryInternal::hunters_mark;
                creators["freezing trap"] = &TriggerFactoryInternal::freezing_trap;
                creators["aspect of the pack"] = &TriggerFactoryInternal::aspect_of_the_pack;
                creators["rapid fire"] = &TriggerFactoryInternal::rapid_fire;
                creators["aspect of the hawk"] = &TriggerFactoryInternal::aspect_of_the_hawk;
                creators["aspect of the wild"] = &TriggerFactoryInternal::aspect_of_the_wild;
            }

        private:
            Trigger* aspect_of_the_viper(AiManagerRegistry* ai) { return new HunterAspectOfTheViperTrigger(ai); }
            Trigger* black_arrow(AiManagerRegistry* ai) { return new BlackArrowTrigger(ai); }
            Trigger* NoStings(AiManagerRegistry* ai) { return new HunterNoStingsActiveTrigger(ai); }
            Trigger* hunters_pet_dead(AiManagerRegistry* ai) { return new HuntersPetDeadTrigger(ai); }
            Trigger* hunters_pet_low_health(AiManagerRegistry* ai) { return new HuntersPetLowHealthTrigger(ai); }
            Trigger* hunters_mark(AiManagerRegistry* ai) { return new HuntersMarkTrigger(ai); }
            Trigger* freezing_trap(AiManagerRegistry* ai) { return new FreezingTrapTrigger(ai); }
            Trigger* aspect_of_the_pack(AiManagerRegistry* ai) { return new HunterAspectOfThePackTrigger(ai); }
            Trigger* rapid_fire(AiManagerRegistry* ai) { return new RapidFireTrigger(ai); }
            Trigger* aspect_of_the_hawk(AiManagerRegistry* ai) { return new HunterAspectOfTheHawkTrigger(ai); }
            Trigger* aspect_of_the_wild(AiManagerRegistry* ai) { return new HunterAspectOfTheWildTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* HunterActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::hunter::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
        {
        public:
            ActionFactoryInternal()
            {
                creators["auto shot"] = &ActionFactoryInternal::auto_shot;
                creators["aimed shot"] = &ActionFactoryInternal::aimed_shot;
                creators["explosive shot"] = &ActionFactoryInternal::explosive_shot;
                creators["arcane shot"] = &ActionFactoryInternal::arcane_shot;
                creators["concussive shot"] = &ActionFactoryInternal::concussive_shot;
                creators["distracting shot"] = &ActionFactoryInternal::distracting_shot;
                creators["multi-shot"] = &ActionFactoryInternal::multi_shot;
                creators["volley"] = &ActionFactoryInternal::volley;
                creators["serpent sting"] = &ActionFactoryInternal::serpent_sting;
                creators["wyvern sting"] = &ActionFactoryInternal::wyvern_sting;
                creators["viper sting"] = &ActionFactoryInternal::viper_sting;
                creators["scorpid sting"] = &ActionFactoryInternal::scorpid_sting;
                creators["hunter's mark"] = &ActionFactoryInternal::hunters_mark;
                creators["mend pet"] = &ActionFactoryInternal::mend_pet;
                creators["revive pet"] = &ActionFactoryInternal::revive_pet;
                creators["call pet"] = &ActionFactoryInternal::call_pet;
                creators["black arrow"] = &ActionFactoryInternal::black_arrow;
                creators["freezing trap"] = &ActionFactoryInternal::freezing_trap;
                creators["rapid fire"] = &ActionFactoryInternal::rapid_fire;
                creators["boost"] = &ActionFactoryInternal::rapid_fire;
                creators["readyness"] = &ActionFactoryInternal::readyness;
                creators["aspect of the hawk"] = &ActionFactoryInternal::aspect_of_the_hawk;
                creators["aspect of the wild"] = &ActionFactoryInternal::aspect_of_the_wild;
                creators["aspect of the viper"] = &ActionFactoryInternal::aspect_of_the_viper;
                creators["aspect of the pack"] = &ActionFactoryInternal::aspect_of_the_pack;
                creators["aspect of the cheetah"] = &ActionFactoryInternal::aspect_of_the_cheetah;
            }

        private:
            Action* auto_shot(AiManagerRegistry* ai) { return new CastAutoShotAction(ai); }
            Action* aimed_shot(AiManagerRegistry* ai) { return new CastAimedShotAction(ai); }
            Action* explosive_shot(AiManagerRegistry* ai) { return new CastExplosiveShotAction(ai); }
            Action* arcane_shot(AiManagerRegistry* ai) { return new CastArcaneShotAction(ai); }
            Action* concussive_shot(AiManagerRegistry* ai) { return new CastConcussiveShotAction(ai); }
            Action* distracting_shot(AiManagerRegistry* ai) { return new CastDistractingShotAction(ai); }
            Action* multi_shot(AiManagerRegistry* ai) { return new CastMultiShotAction(ai); }
            Action* volley(AiManagerRegistry* ai) { return new CastVolleyAction(ai); }
            Action* serpent_sting(AiManagerRegistry* ai) { return new CastSerpentStingAction(ai); }
            Action* wyvern_sting(AiManagerRegistry* ai) { return new CastWyvernStingAction(ai); }
            Action* viper_sting(AiManagerRegistry* ai) { return new CastViperStingAction(ai); }
            Action* scorpid_sting(AiManagerRegistry* ai) { return new CastScorpidStingAction(ai); }
            Action* hunters_mark(AiManagerRegistry* ai) { return new CastHuntersMarkAction(ai); }
            Action* mend_pet(AiManagerRegistry* ai) { return new CastMendPetAction(ai); }
            Action* revive_pet(AiManagerRegistry* ai) { return new CastRevivePetAction(ai); }
            Action* call_pet(AiManagerRegistry* ai) { return new CastCallPetAction(ai); }
            Action* black_arrow(AiManagerRegistry* ai) { return new CastBlackArrow(ai); }
            Action* freezing_trap(AiManagerRegistry* ai) { return new CastFreezingTrap(ai); }
            Action* rapid_fire(AiManagerRegistry* ai) { return new CastRapidFireAction(ai); }
            Action* readyness(AiManagerRegistry* ai) { return new CastReadynessAction(ai); }
            Action* aspect_of_the_hawk(AiManagerRegistry* ai) { return new CastAspectOfTheHawkAction(ai); }
            Action* aspect_of_the_wild(AiManagerRegistry* ai) { return new CastAspectOfTheWildAction(ai); }
            Action* aspect_of_the_viper(AiManagerRegistry* ai) { return new CastAspectOfTheViperAction(ai); }
            Action* aspect_of_the_pack(AiManagerRegistry* ai) { return new CastAspectOfThePackAction(ai); }
            Action* aspect_of_the_cheetah(AiManagerRegistry* ai) { return new CastAspectOfTheCheetahAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* HunterActionFactory::createAction(const char* name)
{
    Action* action = ai::hunter::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
