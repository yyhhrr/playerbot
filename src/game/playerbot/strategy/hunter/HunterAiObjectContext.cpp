#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterActions.h"
#include "HunterTriggers.h"
#include "HunterAiObjectContext.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterBuffStrategies.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
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

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
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

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["auto shot"] = &AiObjectContextInternal::auto_shot;
                creators["aimed shot"] = &AiObjectContextInternal::aimed_shot;
                creators["explosive shot"] = &AiObjectContextInternal::explosive_shot;
                creators["arcane shot"] = &AiObjectContextInternal::arcane_shot;
                creators["concussive shot"] = &AiObjectContextInternal::concussive_shot;
                creators["distracting shot"] = &AiObjectContextInternal::distracting_shot;
                creators["multi-shot"] = &AiObjectContextInternal::multi_shot;
                creators["volley"] = &AiObjectContextInternal::volley;
                creators["serpent sting"] = &AiObjectContextInternal::serpent_sting;
                creators["wyvern sting"] = &AiObjectContextInternal::wyvern_sting;
                creators["viper sting"] = &AiObjectContextInternal::viper_sting;
                creators["scorpid sting"] = &AiObjectContextInternal::scorpid_sting;
                creators["hunter's mark"] = &AiObjectContextInternal::hunters_mark;
                creators["mend pet"] = &AiObjectContextInternal::mend_pet;
                creators["revive pet"] = &AiObjectContextInternal::revive_pet;
                creators["call pet"] = &AiObjectContextInternal::call_pet;
                creators["black arrow"] = &AiObjectContextInternal::black_arrow;
                creators["freezing trap"] = &AiObjectContextInternal::freezing_trap;
                creators["rapid fire"] = &AiObjectContextInternal::rapid_fire;
                creators["boost"] = &AiObjectContextInternal::rapid_fire;
                creators["readyness"] = &AiObjectContextInternal::readyness;
                creators["aspect of the hawk"] = &AiObjectContextInternal::aspect_of_the_hawk;
                creators["aspect of the wild"] = &AiObjectContextInternal::aspect_of_the_wild;
                creators["aspect of the viper"] = &AiObjectContextInternal::aspect_of_the_viper;
                creators["aspect of the pack"] = &AiObjectContextInternal::aspect_of_the_pack;
                creators["aspect of the cheetah"] = &AiObjectContextInternal::aspect_of_the_cheetah;
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

HunterAiObjectContext::HunterAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::hunter::StrategyFactoryInternal());
    actionContexts.Add(new ai::hunter::AiObjectContextInternal());
    triggerContexts.Add(new ai::hunter::TriggerFactoryInternal());    
}