#pragma once

#include "../Strategy.h"

namespace ai
{
    class GenericMageStrategy : public CombatStrategy
    {
    public:
        GenericMageStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        virtual string getName() { return "mage"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
    };
}