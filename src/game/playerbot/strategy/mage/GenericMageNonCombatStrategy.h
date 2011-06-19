#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class GenericMageNonCombatStrategy : public GenericMageStrategy
    {
    public:
        GenericMageNonCombatStrategy(PlayerbotAI* ai) : GenericMageStrategy(ai) {}
        virtual string getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
    };
}