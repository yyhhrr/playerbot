#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueActions.h"
#include "RogueTriggers.h"
#include "RogueActionFactory.h"
#include "DpsRogueStrategy.h"
#include "GenericRogueNonCombatStrategy.h"
#include "../PullStrategy.h"
#include "../NamedObjectFactory.h"

using namespace ai;


namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &rogue::StrategyFactoryInternal::dps;
                creators["nc"] = &rogue::StrategyFactoryInternal::nc;
                creators["pull"] = &rogue::StrategyFactoryInternal::pull;
            }

        private:
            static Strategy* dps(AiManagerRegistry* ai) { return new DpsRogueStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new GenericRogueNonCombatStrategy(ai); }
            static Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        };
    };
};

namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["kick"] = &TriggerFactoryInternal::kick;

            }

        private:
            static Trigger* kick(AiManagerRegistry* ai) { return new KickInterruptSpellTrigger(ai); }
        };
    };
};


namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class ActionFactoryInternal : public NamedObjectFactory<Action>
        {
        public:
            ActionFactoryInternal()
            {
                creators["mutilate"] = &ActionFactoryInternal::mutilate;
                creators["sinister strike"] = &ActionFactoryInternal::sinister_strike;
                creators["kidney shot"] = &ActionFactoryInternal::kidney_shot;
                creators["rupture"] = &ActionFactoryInternal::rupture;
                creators["slice and dice"] = &ActionFactoryInternal::slice_and_dice;
                creators["eviscerate"] = &ActionFactoryInternal::eviscerate;
                creators["vanish"] = &ActionFactoryInternal::vanish;
                creators["evasion"] = &ActionFactoryInternal::evasion;
                creators["kick"] = &ActionFactoryInternal::kick;
                creators["feint"] = &ActionFactoryInternal::feint;
                creators["backstab"] = &ActionFactoryInternal::backstab;
            }

        private:
            static Action* mutilate(AiManagerRegistry* ai) { return new CastMutilateAction(ai); }
            static Action* sinister_strike(AiManagerRegistry* ai) { return new CastSinisterStrikeAction(ai); }
            static Action* kidney_shot(AiManagerRegistry* ai) { return new CastKidneyShotAction(ai); }
            static Action* rupture(AiManagerRegistry* ai) { return new CastRuptureAction(ai); }
            static Action* slice_and_dice(AiManagerRegistry* ai) { return new CastSliceAndDiceAction(ai); }
            static Action* eviscerate(AiManagerRegistry* ai) { return new CastEviscerateAction(ai); }
            static Action* vanish(AiManagerRegistry* ai) { return new CastVanishAction(ai); }
            static Action* evasion(AiManagerRegistry* ai) { return new CastEvasionAction(ai); }
            static Action* kick(AiManagerRegistry* ai) { return new CastKickAction(ai); }
            static Action* feint(AiManagerRegistry* ai) { return new CastFeintAction(ai); }
            static Action* backstab(AiManagerRegistry* ai) { return new CastBackstabAction(ai); }
        };
    };
};

RogueActionFactory::RogueActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai)
{
    strategyFactories.push_back(new ai::rogue::StrategyFactoryInternal());
    actionFactories.push_back(new ai::rogue::ActionFactoryInternal());
    triggerFactories.push_back(new ai::rogue::TriggerFactoryInternal());    
}