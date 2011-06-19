#pragma once

#include "Strategy.h"
#include "AiObjectContext.h"

namespace ai
{
    class GenericNonCombatStrategy : public Strategy
    {
    public:
        GenericNonCombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
		virtual StrategyType GetType() { return STRATEGY_TYPE_NONCOMBAT; }
    };

    class FollowMasterNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        FollowMasterNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "follow master"; }
        virtual NextAction** getDefaultActions();
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual string GetIncompatibleStrategies() { return "-stay,-go away,-follow line,-be near"; }

    };


    class FollowMasterRandomStrategy : public GenericNonCombatStrategy
    {
    public:
        FollowMasterRandomStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "be near"; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string GetIncompatibleStrategies() { return "-stay,-go away,-follow line,-follow master"; }

    };

	class FollowLineNonCombatStrategy : public GenericNonCombatStrategy
	{
	public:
		FollowLineNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual const char* getName() { return "follow line"; }
		virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-stay,-go away,-follow master"; }
	};

    class GoAwayNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GoAwayNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "goaway"; }
        virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-stay,-follow line,-be near,-follow master"; }
    };

    class StayNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        StayNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "stay"; }
        virtual NextAction** getDefaultActions();
		virtual string GetIncompatibleStrategies() { return "-go away,-follow line,-be near,-follow master"; }
    };

    class DpsAssistStrategy : public GenericNonCombatStrategy
    {
    public:
        DpsAssistStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "dps assist"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }
		virtual string GetIncompatibleStrategies() { return "-tank assist,-dps aoe,-tank aoe,-grind"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

	class DpsAoeStrategy : public GenericNonCombatStrategy
	{
	public:
		DpsAoeStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual const char* getName() { return "dps aoe"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }
		virtual string GetIncompatibleStrategies() { return "-tank assist,-dps assist,-tank aoe,-grind"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

    class TankAssistStrategy : public GenericNonCombatStrategy
    {
    public:
        TankAssistStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "tank assist"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_TANK; }
		virtual string GetIncompatibleStrategies() { return "-dps assist,-dps aoe,-tank aoe,-grind"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

	class TankAoeStrategy : public GenericNonCombatStrategy
	{
	public:
		TankAoeStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual const char* getName() { return "tank aoe"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_TANK; }
		virtual string GetIncompatibleStrategies() { return "-tank assist,-dps assist,-dps aoe,-grind"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

    class GrindingStrategy : public GenericNonCombatStrategy
    {
    public:
        GrindingStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "grind"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }
		virtual string GetIncompatibleStrategies() { return "-tank assist,-dps assist,-dps aoe,-tank aoe"; }
		NextAction** getDefaultActions();

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class LootNonCombatStrategy : public Strategy
    {
    public:
        LootNonCombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "loot"; }
    };

    class RandomEmoteStrategy : public Strategy
    {
    public:
        RandomEmoteStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "emote"; }
   };

    class PassiveStrategy : public Strategy
    {
    public:
        PassiveStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "passive"; }
    };

    class LowManaStrategy : public Strategy
    {
    public:
        LowManaStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "low mana"; }
    };

    class UseFoodStrategy : public Strategy
    {
    public:
        UseFoodStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "food"; }
    };
}