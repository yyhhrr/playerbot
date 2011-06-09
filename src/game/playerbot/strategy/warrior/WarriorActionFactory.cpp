#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorActions.h"
#include "WarriorActionFactory.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"
#include "DpsWarriorStrategy.h"
#include "../PullStrategy.h"
#include "WarriorTriggers.h"
#include "../NamedObjectFactory.h"

using namespace ai;


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        static class StrategyFactoryInternal : public NamedObjectFactory<Strategy, warrior::StrategyFactoryInternal>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["tank"] = &warrior::StrategyFactoryInternal::tank;
                creators["dps"] = &warrior::StrategyFactoryInternal::dps;
                creators["nc"] = &warrior::StrategyFactoryInternal::nc;
                creators["pull"] = &warrior::StrategyFactoryInternal::pull;
            }

        private:
            Strategy* tank(AiManagerRegistry* ai) { return new TankWarriorStrategy(ai); }
            Strategy* dps(AiManagerRegistry* ai) { return new DpsWarriorStrategy(ai); }
            Strategy* nc(AiManagerRegistry* ai) { return new GenericWarriorNonCombatStrategy(ai); }
            Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        }
        strategyFactoryInternal;
    };
};

Strategy* WarriorActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ai::warrior::strategyFactoryInternal.create(name, ai);
    return strategy ? strategy : ActionFactory::createStrategy(name);
}

namespace ai
{
    namespace warrior
    {
        using namespace ai;

        static class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["hamstring"] = &TriggerFactoryInternal::hamstring;
                creators["victory rush"] = &TriggerFactoryInternal::victory_rush;
                creators["death wish"] = &TriggerFactoryInternal::death_wish;
                creators["battle shout"] = &TriggerFactoryInternal::battle_shout;
                creators["rend"] = &TriggerFactoryInternal::rend;
                creators["bloodrage"] = &TriggerFactoryInternal::bloodrage;
                creators["shield bash"] = &TriggerFactoryInternal::shield_bash;
                creators["disarm"] = &TriggerFactoryInternal::disarm;
                creators["concussion blow"] = &TriggerFactoryInternal::concussion_blow;
                creators["sword and board"] = &TriggerFactoryInternal::SwordAndBoard;

            }

        private:
            Trigger* hamstring(AiManagerRegistry* ai) { return new HamstringTrigger(ai); }
            Trigger* victory_rush(AiManagerRegistry* ai) { return new VictoryRushTrigger(ai); }
            Trigger* death_wish(AiManagerRegistry* ai) { return new DeathWishTrigger(ai); }
            Trigger* battle_shout(AiManagerRegistry* ai) { return new BattleShoutTrigger(ai); }
            Trigger* rend(AiManagerRegistry* ai) { return new RendDebuffTrigger(ai); }
            Trigger* bloodrage(AiManagerRegistry* ai) { return new BloodrageDebuffTrigger(ai); }
            Trigger* shield_bash(AiManagerRegistry* ai) { return new ShieldBashInterruptSpellTrigger(ai); }
            Trigger* disarm(AiManagerRegistry* ai) { return new DisarmDebuffTrigger(ai); }
            Trigger* concussion_blow(AiManagerRegistry* ai) { return new ConcussionBlowTrigger(ai); }
            Trigger* SwordAndBoard(AiManagerRegistry* ai) { return new SwordAndBoardTrigger(ai); }
        }
        triggerFactoryInternal;
    };
};

Trigger* WarriorActionFactory::createTrigger(const char* name)
{
    Trigger* trigger = ai::warrior::triggerFactoryInternal.create(name, ai);
    return trigger ? trigger : ActionFactory::createTrigger(name);
}


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        static class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
        {
        public:
            ActionFactoryInternal()
            {
                creators["devastate"] = &ActionFactoryInternal::devastate;
                creators["overpower"] = &ActionFactoryInternal::overpower;
                creators["charge"] = &ActionFactoryInternal::charge;
                creators["bloodthirst"] = &ActionFactoryInternal::bloodthirst;
                creators["rend"] = &ActionFactoryInternal::rend;
                creators["mocking blow"] = &ActionFactoryInternal::mocking_blow;
                creators["death wish"] = &ActionFactoryInternal::death_wish;
                creators["berserker rage"] = &ActionFactoryInternal::berserker_rage;
                creators["victory rush"] = &ActionFactoryInternal::victory_rush;
                creators["execute"] = &ActionFactoryInternal::execute;
                creators["defensive stance"] = &ActionFactoryInternal::defensive_stance;
                creators["hamstring"] = &ActionFactoryInternal::hamstring;
                creators["shield bash"] = &ActionFactoryInternal::shield_bash;
                creators["shield block"] = &ActionFactoryInternal::shield_block;
                creators["bloodrage"] = &ActionFactoryInternal::bloodrage;
                creators["battle stance"] = &ActionFactoryInternal::battle_stance;
                creators["heroic strike"] = &ActionFactoryInternal::heroic_strike;
                creators["intimidating shout"] = &ActionFactoryInternal::intimidating_shout;
                creators["demoralizing shout"] = &ActionFactoryInternal::demoralizing_shout;
                creators["challenging shout"] = &ActionFactoryInternal::challenging_shout;
                creators["shield wall"] = &ActionFactoryInternal::shield_wall;
                creators["battle shout"] = &ActionFactoryInternal::battle_shout;
                creators["thunder clap"] = &ActionFactoryInternal::thunder_clap;
                creators["taunt"] = &ActionFactoryInternal::taunt;
                creators["revenge"] = &ActionFactoryInternal::revenge;
                creators["slam"] = &ActionFactoryInternal::slam;
                creators["shield slam"] = &ActionFactoryInternal::shield_slam;
                creators["disarm"] = &ActionFactoryInternal::disarm;
                creators["sunder armor"] = &ActionFactoryInternal::sunder_armor;
                creators["last stand"] = &ActionFactoryInternal::last_stand;
                creators["shockwave"] = &ActionFactoryInternal::shockwave;
                creators["concussion blow"] = &ActionFactoryInternal::concussion_blow;
            }

        private:
            Action* devastate(AiManagerRegistry* ai) { return new CastDevastateAction(ai); }
            Action* last_stand(AiManagerRegistry* ai) { return new CastLastStandAction(ai); }
            Action* shockwave(AiManagerRegistry* ai) { return new CastShockwaveAction(ai); }
            Action* concussion_blow(AiManagerRegistry* ai) { return new CastConcussionBlowAction(ai); }
            Action* taunt(AiManagerRegistry* ai) { return new CastTauntAction(ai); }
            Action* revenge(AiManagerRegistry* ai) { return new CastRevengeAction(ai); }
            Action* slam(AiManagerRegistry* ai) { return new CastSlamAction(ai); }
            Action* shield_slam(AiManagerRegistry* ai) { return new CastShieldSlamAction(ai); }
            Action* disarm(AiManagerRegistry* ai) { return new CastDisarmAction(ai); }
            Action* sunder_armor(AiManagerRegistry* ai) { return new CastSunderArmorAction(ai); }
            Action* overpower(AiManagerRegistry* ai) { return new CastOverpowerAction(ai); }
            Action* charge(AiManagerRegistry* ai) { return new CastChargeAction(ai); }
            Action* bloodthirst(AiManagerRegistry* ai) { return new CastBloodthirstAction(ai); }
            Action* rend(AiManagerRegistry* ai) { return new CastRendAction(ai); }
            Action* mocking_blow(AiManagerRegistry* ai) { return new CastMockingBlowAction(ai); }
            Action* death_wish(AiManagerRegistry* ai) { return new CastDeathWishAction(ai); }
            Action* berserker_rage(AiManagerRegistry* ai) { return new CastBerserkerRageAction(ai); }
            Action* victory_rush(AiManagerRegistry* ai) { return new CastVictoryRushAction(ai); }
            Action* execute(AiManagerRegistry* ai) { return new CastExecuteAction(ai); }
            Action* defensive_stance(AiManagerRegistry* ai) { return new CastDefensiveStanceAction(ai); }
            Action* hamstring(AiManagerRegistry* ai) { return new CastHamstringAction(ai); }
            Action* shield_bash(AiManagerRegistry* ai) { return new CastShieldBashAction(ai); }
            Action* shield_block(AiManagerRegistry* ai) { return new CastShieldBlockAction(ai); }
            Action* bloodrage(AiManagerRegistry* ai) { return new CastBloodrageAction(ai); }
            Action* battle_stance(AiManagerRegistry* ai) { return new CastBattleStanceAction(ai); }
            Action* heroic_strike(AiManagerRegistry* ai) { return new CastHeroicStrikeAction(ai); }
            Action* intimidating_shout(AiManagerRegistry* ai) { return new CastIntimidatingShoutAction(ai); }
            Action* demoralizing_shout(AiManagerRegistry* ai) { return new CastDemoralizingShoutAction(ai); }
            Action* challenging_shout(AiManagerRegistry* ai) { return new CastChallengingShoutAction(ai); }
            Action* shield_wall(AiManagerRegistry* ai) { return new CastShieldWallAction(ai); }
            Action* battle_shout(AiManagerRegistry* ai) { return new CastBattleShoutAction(ai); }
            Action* thunder_clap(AiManagerRegistry* ai) { return new CastThunderClapAction(ai); }

        }
        actionFactoryInternal;
    };
};

Action* WarriorActionFactory::createAction(const char* name)
{
    Action* action = ai::warrior::actionFactoryInternal.create(name, ai);
    return action ? action : ActionFactory::createAction(name);
}
