#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueActions.h"
#include "RogueTriggers.h"
#include "RogueAiObjectContext.h"
#include "DpsRogueStrategy.h"
#include "GenericRogueNonCombatStrategy.h"
#include "../PullStrategy.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace rogue
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
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

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
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

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["mutilate"] = &AiObjectContextInternal::mutilate;
                creators["sinister strike"] = &AiObjectContextInternal::sinister_strike;
                creators["kidney shot"] = &AiObjectContextInternal::kidney_shot;
                creators["rupture"] = &AiObjectContextInternal::rupture;
                creators["slice and dice"] = &AiObjectContextInternal::slice_and_dice;
                creators["eviscerate"] = &AiObjectContextInternal::eviscerate;
                creators["vanish"] = &AiObjectContextInternal::vanish;
                creators["evasion"] = &AiObjectContextInternal::evasion;
                creators["kick"] = &AiObjectContextInternal::kick;
                creators["feint"] = &AiObjectContextInternal::feint;
                creators["backstab"] = &AiObjectContextInternal::backstab;
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

RogueAiObjectContext::RogueAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::rogue::StrategyFactoryInternal());
    actionContexts.Add(new ai::rogue::AiObjectContextInternal());
    triggerContexts.Add(new ai::rogue::TriggerFactoryInternal());    
}