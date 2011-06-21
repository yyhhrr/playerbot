#pragma once;

#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"
#include "ChatCommandHandlerStrategy.h"
#include "WorldPacketHandlerStrategy.h"
#include "DeadStrategy.h"

namespace ai
{
    class StrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        StrategyContext()
        {
            creators["racials"] = &StrategyContext::racials;
            creators["dps assist"] = &StrategyContext::dps_assist;
            creators["dps aoe"] = &StrategyContext::dps_aoe;
            creators["tank assist"] = &StrategyContext::tank_assist;
            creators["tank aoe"] = &StrategyContext::tank_aoe;
            creators["grind"] = &StrategyContext::grind;
            creators["loot"] = &StrategyContext::loot;
            creators["emote"] = &StrategyContext::emote;
            creators["passive"] = &StrategyContext::passive;
            creators["low mana"] = &StrategyContext::low_mana;
            creators["food"] = &StrategyContext::food;
            creators["chat"] = &StrategyContext::chat;
            creators["world packet"] = &StrategyContext::world_packet;
            creators["dead"] = &StrategyContext::dead;
        }

    private:
        static Strategy* dead(PlayerbotAI* ai) { return new DeadStrategy(ai); }
        static Strategy* racials(PlayerbotAI* ai) { return new RacialsStrategy(ai); }
        static Strategy* dps_assist(PlayerbotAI* ai) { return new DpsAssistStrategy(ai); }
        static Strategy* dps_aoe(PlayerbotAI* ai) { return new DpsAoeStrategy(ai); }
        static Strategy* tank_assist(PlayerbotAI* ai) { return new TankAssistStrategy(ai); }
        static Strategy* tank_aoe(PlayerbotAI* ai) { return new TankAoeStrategy(ai); }
        static Strategy* grind(PlayerbotAI* ai) { return new GrindingStrategy(ai); }
        static Strategy* loot(PlayerbotAI* ai) { return new LootNonCombatStrategy(ai); }
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
        }

    private:
        static Strategy* follow_master_random(PlayerbotAI* ai) { return new FollowMasterRandomStrategy(ai); }
        static Strategy* follow_master(PlayerbotAI* ai) { return new FollowMasterNonCombatStrategy(ai); }
        static Strategy* follow_line(PlayerbotAI* ai) { return new FollowLineNonCombatStrategy(ai); }
        static Strategy* stay(PlayerbotAI* ai) { return new StayNonCombatStrategy(ai); }
        static Strategy* goaway(PlayerbotAI* ai) { return new GoAwayNonCombatStrategy(ai); }
    };
};
