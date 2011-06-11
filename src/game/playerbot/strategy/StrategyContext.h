#pragma once;

namespace ai
{
    class StrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        StrategyContext()
        {
            creators["racials"] = &StrategyContext::racials;
            creators["follow master"] = &StrategyContext::follow_master;
            creators["follow line"] = &StrategyContext::follow_line;
            creators["stay"] = &StrategyContext::stay;
            creators["dps assist"] = &StrategyContext::dps_assist;
            creators["dps aoe"] = &StrategyContext::dps_aoe;
            creators["tank assist"] = &StrategyContext::tank_assist;
            creators["tank aoe"] = &StrategyContext::tank_aoe;
            creators["grind"] = &StrategyContext::grind;
            creators["loot"] = &StrategyContext::loot;
            creators["goaway"] = &StrategyContext::goaway;
            creators["emote"] = &StrategyContext::emote;
            creators["passive"] = &StrategyContext::passive;
            creators["low mana"] = &StrategyContext::low_mana;
            creators["food"] = &StrategyContext::food;
            creators["chat"] = &StrategyContext::chat;
        }

    private:
        static Strategy* racials(AiManagerRegistry* ai) { return new RacialsStrategy(ai); }
        static Strategy* follow_master(AiManagerRegistry* ai) { return new FollowMasterNonCombatStrategy(ai); }
        static Strategy* follow_line(AiManagerRegistry* ai) { return new FollowLineNonCombatStrategy(ai); }
        static Strategy* stay(AiManagerRegistry* ai) { return new StayNonCombatStrategy(ai); }
        static Strategy* dps_assist(AiManagerRegistry* ai) { return new DpsAssistStrategy(ai); }
        static Strategy* dps_aoe(AiManagerRegistry* ai) { return new DpsAoeStrategy(ai); }
        static Strategy* tank_assist(AiManagerRegistry* ai) { return new TankAssistStrategy(ai); }
        static Strategy* tank_aoe(AiManagerRegistry* ai) { return new TankAoeStrategy(ai); }
        static Strategy* grind(AiManagerRegistry* ai) { return new GrindingStrategy(ai); }
        static Strategy* loot(AiManagerRegistry* ai) { return new LootNonCombatStrategy(ai); }
        static Strategy* goaway(AiManagerRegistry* ai) { return new GoAwayNonCombatStrategy(ai); }
        static Strategy* emote(AiManagerRegistry* ai) { return new RandomEmoteStrategy(ai); }
        static Strategy* passive(AiManagerRegistry* ai) { return new PassiveStrategy(ai); }
        static Strategy* low_mana(AiManagerRegistry* ai) { return new LowManaStrategy(ai); }
        static Strategy* food(AiManagerRegistry* ai) { return new UseFoodStrategy(ai); }
        static Strategy* chat(AiManagerRegistry* ai) { return new ChatCommandHandlerStrategy(ai); }
    };

};