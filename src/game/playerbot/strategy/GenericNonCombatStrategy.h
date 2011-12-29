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
        virtual string getName() { return "follow master"; }
        virtual NextAction** getDefaultActions();
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);

    };


    class FollowMasterRandomStrategy : public GenericNonCombatStrategy
    {
    public:
        FollowMasterRandomStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "be near"; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);

    };

	class FollowLineNonCombatStrategy : public GenericNonCombatStrategy
	{
	public:
		FollowLineNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "follow line"; }
		virtual NextAction** getDefaultActions();
	};

    class RunAwayStrategy : public GenericNonCombatStrategy
    {
    public:
        RunAwayStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "runaway"; }
        virtual NextAction** getDefaultActions();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class StayCircleStrategy : public GenericNonCombatStrategy
    {
    public:
        StayCircleStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "stay circle"; }
        virtual NextAction** getDefaultActions();
    };

    class StayLineStrategy : public GenericNonCombatStrategy
    {
    public:
        StayLineStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "stay line"; }
        virtual NextAction** getDefaultActions();
    };

    class StayCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        StayCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "stay combat"; }
        virtual NextAction** getDefaultActions();
    };

    class StayNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        StayNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "stay"; }
        virtual NextAction** getDefaultActions();
    };

    class DpsAssistStrategy : public GenericNonCombatStrategy
    {
    public:
        DpsAssistStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "dps assist"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

	class DpsAoeStrategy : public GenericNonCombatStrategy
	{
	public:
		DpsAoeStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "dps aoe"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

    class TankAssistStrategy : public GenericNonCombatStrategy
    {
    public:
        TankAssistStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "tank assist"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_TANK; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

	class TankAoeStrategy : public GenericNonCombatStrategy
	{
	public:
		TankAoeStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "tank aoe"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_TANK; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

	class AttackWeakStrategy : public GenericNonCombatStrategy
	{
	public:
	    AttackWeakStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "attack weak"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

	class AttackRtiStrategy : public GenericNonCombatStrategy
	{
	public:
	    AttackRtiStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
		virtual string getName() { return "attack rti"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
	};

    class GrindingStrategy : public GenericNonCombatStrategy
    {
    public:
        GrindingStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "grind"; }
		virtual StrategyType GetType() { return STRATEGY_TYPE_DPS; }
		NextAction** getDefaultActions();

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class RandomEmoteStrategy : public Strategy
    {
    public:
        RandomEmoteStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "emote"; }
   };

    class PassiveStrategy : public Strategy
    {
    public:
        PassiveStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "passive"; }
    };

    class LowManaStrategy : public Strategy
    {
    public:
        LowManaStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "low mana"; }
    };

    class UseFoodStrategy : public Strategy
    {
    public:
        UseFoodStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "food"; }
    };
}
