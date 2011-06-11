#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorActions.h"
#include "WarriorAiObjectContext.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"
#include "DpsWarriorStrategy.h"
#include "../PullStrategy.h"
#include "WarriorTriggers.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
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
            static Strategy* tank(AiManagerRegistry* ai) { return new TankWarriorStrategy(ai); }
            static Strategy* dps(AiManagerRegistry* ai) { return new DpsWarriorStrategy(ai); }
            static Strategy* nc(AiManagerRegistry* ai) { return new GenericWarriorNonCombatStrategy(ai); }
            static Strategy* pull(AiManagerRegistry* ai) { return new PullStrategy(ai, "shoot"); }
        };
    };
};

namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
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
            static Trigger* hamstring(AiManagerRegistry* ai) { return new HamstringTrigger(ai); }
            static Trigger* victory_rush(AiManagerRegistry* ai) { return new VictoryRushTrigger(ai); }
            static Trigger* death_wish(AiManagerRegistry* ai) { return new DeathWishTrigger(ai); }
            static Trigger* battle_shout(AiManagerRegistry* ai) { return new BattleShoutTrigger(ai); }
            static Trigger* rend(AiManagerRegistry* ai) { return new RendDebuffTrigger(ai); }
            static Trigger* bloodrage(AiManagerRegistry* ai) { return new BloodrageDebuffTrigger(ai); }
            static Trigger* shield_bash(AiManagerRegistry* ai) { return new ShieldBashInterruptSpellTrigger(ai); }
            static Trigger* disarm(AiManagerRegistry* ai) { return new DisarmDebuffTrigger(ai); }
            static Trigger* concussion_blow(AiManagerRegistry* ai) { return new ConcussionBlowTrigger(ai); }
            static Trigger* SwordAndBoard(AiManagerRegistry* ai) { return new SwordAndBoardTrigger(ai); }
        };
    };
};


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["devastate"] = &AiObjectContextInternal::devastate;
                creators["overpower"] = &AiObjectContextInternal::overpower;
                creators["charge"] = &AiObjectContextInternal::charge;
                creators["bloodthirst"] = &AiObjectContextInternal::bloodthirst;
                creators["rend"] = &AiObjectContextInternal::rend;
                creators["mocking blow"] = &AiObjectContextInternal::mocking_blow;
                creators["death wish"] = &AiObjectContextInternal::death_wish;
                creators["berserker rage"] = &AiObjectContextInternal::berserker_rage;
                creators["victory rush"] = &AiObjectContextInternal::victory_rush;
                creators["execute"] = &AiObjectContextInternal::execute;
                creators["defensive stance"] = &AiObjectContextInternal::defensive_stance;
                creators["hamstring"] = &AiObjectContextInternal::hamstring;
                creators["shield bash"] = &AiObjectContextInternal::shield_bash;
                creators["shield block"] = &AiObjectContextInternal::shield_block;
                creators["bloodrage"] = &AiObjectContextInternal::bloodrage;
                creators["battle stance"] = &AiObjectContextInternal::battle_stance;
                creators["heroic strike"] = &AiObjectContextInternal::heroic_strike;
                creators["intimidating shout"] = &AiObjectContextInternal::intimidating_shout;
                creators["demoralizing shout"] = &AiObjectContextInternal::demoralizing_shout;
                creators["challenging shout"] = &AiObjectContextInternal::challenging_shout;
                creators["shield wall"] = &AiObjectContextInternal::shield_wall;
                creators["battle shout"] = &AiObjectContextInternal::battle_shout;
                creators["thunder clap"] = &AiObjectContextInternal::thunder_clap;
                creators["taunt"] = &AiObjectContextInternal::taunt;
                creators["revenge"] = &AiObjectContextInternal::revenge;
                creators["slam"] = &AiObjectContextInternal::slam;
                creators["shield slam"] = &AiObjectContextInternal::shield_slam;
                creators["disarm"] = &AiObjectContextInternal::disarm;
                creators["sunder armor"] = &AiObjectContextInternal::sunder_armor;
                creators["last stand"] = &AiObjectContextInternal::last_stand;
                creators["shockwave"] = &AiObjectContextInternal::shockwave;
                creators["concussion blow"] = &AiObjectContextInternal::concussion_blow;
            }

        private:
            static Action* devastate(AiManagerRegistry* ai) { return new CastDevastateAction(ai); }
            static Action* last_stand(AiManagerRegistry* ai) { return new CastLastStandAction(ai); }
            static Action* shockwave(AiManagerRegistry* ai) { return new CastShockwaveAction(ai); }
            static Action* concussion_blow(AiManagerRegistry* ai) { return new CastConcussionBlowAction(ai); }
            static Action* taunt(AiManagerRegistry* ai) { return new CastTauntAction(ai); }
            static Action* revenge(AiManagerRegistry* ai) { return new CastRevengeAction(ai); }
            static Action* slam(AiManagerRegistry* ai) { return new CastSlamAction(ai); }
            static Action* shield_slam(AiManagerRegistry* ai) { return new CastShieldSlamAction(ai); }
            static Action* disarm(AiManagerRegistry* ai) { return new CastDisarmAction(ai); }
            static Action* sunder_armor(AiManagerRegistry* ai) { return new CastSunderArmorAction(ai); }
            static Action* overpower(AiManagerRegistry* ai) { return new CastOverpowerAction(ai); }
            static Action* charge(AiManagerRegistry* ai) { return new CastChargeAction(ai); }
            static Action* bloodthirst(AiManagerRegistry* ai) { return new CastBloodthirstAction(ai); }
            static Action* rend(AiManagerRegistry* ai) { return new CastRendAction(ai); }
            static Action* mocking_blow(AiManagerRegistry* ai) { return new CastMockingBlowAction(ai); }
            static Action* death_wish(AiManagerRegistry* ai) { return new CastDeathWishAction(ai); }
            static Action* berserker_rage(AiManagerRegistry* ai) { return new CastBerserkerRageAction(ai); }
            static Action* victory_rush(AiManagerRegistry* ai) { return new CastVictoryRushAction(ai); }
            static Action* execute(AiManagerRegistry* ai) { return new CastExecuteAction(ai); }
            static Action* defensive_stance(AiManagerRegistry* ai) { return new CastDefensiveStanceAction(ai); }
            static Action* hamstring(AiManagerRegistry* ai) { return new CastHamstringAction(ai); }
            static Action* shield_bash(AiManagerRegistry* ai) { return new CastShieldBashAction(ai); }
            static Action* shield_block(AiManagerRegistry* ai) { return new CastShieldBlockAction(ai); }
            static Action* bloodrage(AiManagerRegistry* ai) { return new CastBloodrageAction(ai); }
            static Action* battle_stance(AiManagerRegistry* ai) { return new CastBattleStanceAction(ai); }
            static Action* heroic_strike(AiManagerRegistry* ai) { return new CastHeroicStrikeAction(ai); }
            static Action* intimidating_shout(AiManagerRegistry* ai) { return new CastIntimidatingShoutAction(ai); }
            static Action* demoralizing_shout(AiManagerRegistry* ai) { return new CastDemoralizingShoutAction(ai); }
            static Action* challenging_shout(AiManagerRegistry* ai) { return new CastChallengingShoutAction(ai); }
            static Action* shield_wall(AiManagerRegistry* ai) { return new CastShieldWallAction(ai); }
            static Action* battle_shout(AiManagerRegistry* ai) { return new CastBattleShoutAction(ai); }
            static Action* thunder_clap(AiManagerRegistry* ai) { return new CastThunderClapAction(ai); }

        };
    };
};

WarriorAiObjectContext::WarriorAiObjectContext(AiManagerRegistry* const ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::warrior::StrategyFactoryInternal());
    actionContexts.Add(new ai::warrior::AiObjectContextInternal());
    triggerContexts.Add(new ai::warrior::TriggerFactoryInternal());    
}