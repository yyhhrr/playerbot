#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"
#include "NamedObjectContext.h"

namespace ai
{
	enum StrategyType
	{
		STRATEGY_TYPE_GENERIC = 0,
		STRATEGY_TYPE_COMBAT = 1,
		STRATEGY_TYPE_NONCOMBAT = 2,
		STRATEGY_TYPE_TANK = 4,
		STRATEGY_TYPE_DPS = 8,
		STRATEGY_TYPE_HEAL = 16,
	};

    class Strategy : public PlayerbotAIAware
    {
    public:
        Strategy(PlayerbotAI* ai);
        virtual ~Strategy() {}

    public:
        virtual NextAction** getDefaultActions() { return NULL; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers) {}
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers) {}
        virtual string getName() = 0;
		virtual StrategyType GetType() { return STRATEGY_TYPE_GENERIC; }
        virtual ActionNode* GetAction(string name);
        void Update() {}

    protected:
        NamedObjectFactoryList<ActionNode> actionNodeFactories;
    };

    class CombatStrategy : public Strategy
    {
    public:
        CombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual StrategyType GetType() { return STRATEGY_TYPE_COMBAT; }
    };


    class MeleeCombatStrategy : public CombatStrategy
    {
    public:
        MeleeCombatStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };


    class RangedCombatStrategy : public CombatStrategy
    {
    public:
        RangedCombatStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
