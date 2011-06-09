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

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, rogue::StrategyFactoryInternal>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &rogue::StrategyFactoryInternal::dps;
                creators["nc"] = &rogue::StrategyFactoryInternal::nc;
                creators["pull"] = &rogue::StrategyFactoryInternal::pull;
            }

        private:
            Strategy* dps(AiManagerRegistry* ai) { return new DpsRogueStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericRogueNonCombatStrategy(ai); }
            Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        }
        strategyFactoryInternal;
    };
};

Strategy* RogueActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::rogue::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace rogue
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["kick"] = &TriggerFactoryInternal::kick;

            }

        private:
            Trigger* kick(AiManagerRegistry* ai) { return new KickInterruptSpellTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* RogueActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::rogue::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace rogue
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
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
            Action* mutilate(AiManagerRegistry* ai) { return new CastMutilateAction(ai); }
            Action* sinister_strike(AiManagerRegistry* ai) { return new CastSinisterStrikeAction(ai); }
            Action* kidney_shot(AiManagerRegistry* ai) { return new CastKidneyShotAction(ai); }
            Action* rupture(AiManagerRegistry* ai) { return new CastRuptureAction(ai); }
            Action* slice_and_dice(AiManagerRegistry* ai) { return new CastSliceAndDiceAction(ai); }
            Action* eviscerate(AiManagerRegistry* ai) { return new CastEviscerateAction(ai); }
            Action* vanish(AiManagerRegistry* ai) { return new CastVanishAction(ai); }
            Action* evasion(AiManagerRegistry* ai) { return new CastEvasionAction(ai); }
            Action* kick(AiManagerRegistry* ai) { return new CastKickAction(ai); }
            Action* feint(AiManagerRegistry* ai) { return new CastFeintAction(ai); }
            Action* backstab(AiManagerRegistry* ai) { return new CastBackstabAction(ai); }
        }
        actionFactoryInternal;
    };
};

Action* RogueActionFactory::createAction(const char* name)
{
    Action* action = ai::rogue::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
