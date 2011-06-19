#pragma once

#include "../GenericNonCombatStrategy.h"

namespace ai
{
    class GenericPaladinNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericPaladinNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
   };
}