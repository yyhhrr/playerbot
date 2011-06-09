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

        class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
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
            static Strategy* dps(AiManagerRegistry* ai) { return new DpsHunterStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new GenericHunterNonCombatStrategy(ai); }
            static Strategy* bspeed(AiManagerRegistry* ai) { return new HunterBuffSpeedNonCombatStrategy(ai); }
            static Strategy* bdps(AiManagerRegistry* ai) { return new HunterBuffDpsStrategy(ai); }
            static Strategy* rnature(AiManagerRegistry* ai) { return new HunterNatureResistanceStrategy(ai); }
        };
    };
};


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
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
            static Trigger* aspect_of_the_viper(AiManagerRegistry* ai) { return new HunterAspectOfTheViperTrigger(ai); }
            static Trigger* black_arrow(AiManagerRegistry* ai) { return new BlackArrowTrigger(ai); }
            static Trigger* NoStings(AiManagerRegistry* ai) { return new HunterNoStingsActiveTrigger(ai); }
            static Trigger* hunters_pet_dead(AiManagerRegistry* ai) { return new HuntersPetDeadTrigger(ai); }
            static Trigger* hunters_pet_low_health(AiManagerRegistry* ai) { return new HuntersPetLowHealthTrigger(ai); }
            static Trigger* hunters_mark(AiManagerRegistry* ai) { return new HuntersMarkTrigger(ai); }
            static Trigger* freezing_trap(AiManagerRegistry* ai) { return new FreezingTrapTrigger(ai); }
            static Trigger* aspect_of_the_pack(AiManagerRegistry* ai) { return new HunterAspectOfThePackTrigger(ai); }
            static Trigger* rapid_fire(AiManagerRegistry* ai) { return new RapidFireTrigger(ai); }
            static Trigger* aspect_of_the_hawk(AiManagerRegistry* ai) { return new HunterAspectOfTheHawkTrigger(ai); }
            static Trigger* aspect_of_the_wild(AiManagerRegistry* ai) { return new HunterAspectOfTheWildTrigger(ai); }
        };
    };
};



namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class ActionFactoryInternal : public NamedObjectFactory<Action>
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
            static Action* auto_shot(AiManagerRegistry* ai) { return new CastAutoShotAction(ai); }
            static Action* aimed_shot(AiManagerRegistry* ai) { return new CastAimedShotAction(ai); }
            static Action* explosive_shot(AiManagerRegistry* ai) { return new CastExplosiveShotAction(ai); }
            static Action* arcane_shot(AiManagerRegistry* ai) { return new CastArcaneShotAction(ai); }
            static Action* concussive_shot(AiManagerRegistry* ai) { return new CastConcussiveShotAction(ai); }
            static Action* distracting_shot(AiManagerRegistry* ai) { return new CastDistractingShotAction(ai); }
            static Action* multi_shot(AiManagerRegistry* ai) { return new CastMultiShotAction(ai); }
            static Action* volley(AiManagerRegistry* ai) { return new CastVolleyAction(ai); }
            static Action* serpent_sting(AiManagerRegistry* ai) { return new CastSerpentStingAction(ai); }
            static Action* wyvern_sting(AiManagerRegistry* ai) { return new CastWyvernStingAction(ai); }
            static Action* viper_sting(AiManagerRegistry* ai) { return new CastViperStingAction(ai); }
            static Action* scorpid_sting(AiManagerRegistry* ai) { return new CastScorpidStingAction(ai); }
            static Action* hunters_mark(AiManagerRegistry* ai) { return new CastHuntersMarkAction(ai); }
            static Action* mend_pet(AiManagerRegistry* ai) { return new CastMendPetAction(ai); }
            static Action* revive_pet(AiManagerRegistry* ai) { return new CastRevivePetAction(ai); }
            static Action* call_pet(AiManagerRegistry* ai) { return new CastCallPetAction(ai); }
            static Action* black_arrow(AiManagerRegistry* ai) { return new CastBlackArrow(ai); }
            static Action* freezing_trap(AiManagerRegistry* ai) { return new CastFreezingTrap(ai); }
            static Action* rapid_fire(AiManagerRegistry* ai) { return new CastRapidFireAction(ai); }
            static Action* readyness(AiManagerRegistry* ai) { return new CastReadynessAction(ai); }
            static Action* aspect_of_the_hawk(AiManagerRegistry* ai) { return new CastAspectOfTheHawkAction(ai); }
            static Action* aspect_of_the_wild(AiManagerRegistry* ai) { return new CastAspectOfTheWildAction(ai); }
            static Action* aspect_of_the_viper(AiManagerRegistry* ai) { return new CastAspectOfTheViperAction(ai); }
            static Action* aspect_of_the_pack(AiManagerRegistry* ai) { return new CastAspectOfThePackAction(ai); }
            static Action* aspect_of_the_cheetah(AiManagerRegistry* ai) { return new CastAspectOfTheCheetahAction(ai); }
        };
    };
};

HunterActionFactory::HunterActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai)
{
    strategyFactories.push_back(new ai::hunter::StrategyFactoryInternal());
    actionFactories.push_back(new ai::hunter::ActionFactoryInternal());
    triggerFactories.push_back(new ai::hunter::TriggerFactoryInternal());    
}