#pragma once;

#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"
#include "ChatCommandHandlerStrategy.h"
#include "WorldPacketHandlerStrategy.h"
#include "DeadStrategy.h"
#include "QuestStrategies.h"
#include "LootNonCombatStrategy.h"
#include "DuelStrategy.h"

namespace ai
{
    class StrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        StrategyContext()
        {
            creators["racials"] = &StrategyContext::racials;
            creators["loot"] = &StrategyContext::loot;
            creators["gather"] = &StrategyContext::gather;
            creators["emote"] = &StrategyContext::emote;
            creators["passive"] = &StrategyContext::passive;
            creators["low mana"] = &StrategyContext::low_mana;
            creators["food"] = &StrategyContext::food;
            creators["chat"] = &StrategyContext::chat;
            creators["world packet"] = &StrategyContext::world_packet;
            creators["dead"] = &StrategyContext::dead;
            creators["flee"] = &StrategyContext::flee;
            creators["duel"] = &StrategyContext::duel;
        }

    private:
        static Strategy* duel(PlayerbotAI* ai) { return new DuelStrategy(ai); }
        static Strategy* flee(PlayerbotAI* ai) { return new FleeStrategy(ai); }
        static Strategy* dead(PlayerbotAI* ai) { return new DeadStrategy(ai); }
        static Strategy* racials(PlayerbotAI* ai) { return new RacialsStrategy(ai); }
        static Strategy* loot(PlayerbotAI* ai) { return new LootNonCombatStrategy(ai); }
        static Strategy* gather(PlayerbotAI* ai) { return new GatherStrategy(ai); }
        static Strategy* emote(PlayerbotAI* ai) { return new RandomEmoteStrategy(ai); }
        static Strategy* passive(PlayerbotAI* ai) { return new PassiveStrategy(ai); }
        static Strategy* low_mana(PlayerbotAI* ai) { return new LowManaStrategy(ai); }
        static Strategy* food(PlayerbotAI* ai) { return new UseFoodStrategy(ai); }
        static Strategy* chat(PlayerbotAI* ai) { return new ChatCommandHandlerStrategy(ai); }
        static Strategy* world_packet(PlayerbotAI* ai) { return new WorldPacketHandlerStrategy(ai); }
    };

    class MovementStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        MovementStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["follow master"] = &MovementStrategyContext::follow_master;
            creators["be near"] = &MovementStrategyContext::follow_master_random;
            creators["follow line"] = &MovementStrategyContext::follow_line;
            creators["stay"] = &MovementStrategyContext::stay;
            creators["goaway"] = &MovementStrategyContext::goaway;
            creators["stay circle"] = &MovementStrategyContext::stay_circle;
        }

    private:
        static Strategy* follow_master_random(PlayerbotAI* ai) { return new FollowMasterRandomStrategy(ai); }
        static Strategy* follow_master(PlayerbotAI* ai) { return new FollowMasterNonCombatStrategy(ai); }
        static Strategy* follow_line(PlayerbotAI* ai) { return new FollowLineNonCombatStrategy(ai); }
        static Strategy* stay(PlayerbotAI* ai) { return new StayNonCombatStrategy(ai); }
        static Strategy* goaway(PlayerbotAI* ai) { return new GoAwayNonCombatStrategy(ai); }
        static Strategy* stay_circle(PlayerbotAI* ai) { return new StayCircleStrategy(ai); }
    };

    class AssistStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        AssistStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["dps assist"] = &AssistStrategyContext::dps_assist;
            creators["dps aoe"] = &AssistStrategyContext::dps_aoe;
            creators["tank assist"] = &AssistStrategyContext::tank_assist;
            creators["tank aoe"] = &AssistStrategyContext::tank_aoe;
            creators["attack weak"] = &AssistStrategyContext::attack_weak;
            creators["grind"] = &AssistStrategyContext::grind;
        }

    private:
        static Strategy* dps_assist(PlayerbotAI* ai) { return new DpsAssistStrategy(ai); }
        static Strategy* dps_aoe(PlayerbotAI* ai) { return new DpsAoeStrategy(ai); }
        static Strategy* tank_assist(PlayerbotAI* ai) { return new TankAssistStrategy(ai); }
        static Strategy* tank_aoe(PlayerbotAI* ai) { return new TankAoeStrategy(ai); }
        static Strategy* attack_weak(PlayerbotAI* ai) { return new AttackWeakStrategy(ai); }
        static Strategy* grind(PlayerbotAI* ai) { return new GrindingStrategy(ai); }
    };

    class QuestStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        QuestStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["quest"] = &QuestStrategyContext::quest;
            creators["accept all quests"] = &QuestStrategyContext::accept_all_quests;
        }

    private:
        static Strategy* quest(PlayerbotAI* ai) { return new DefaultQuestStrategy(ai); }
        static Strategy* accept_all_quests(PlayerbotAI* ai) { return new AcceptAllQuestsStrategy(ai); }
    };
};
