#pragma once

#include "../GenericNonCombatStrategy.h"

namespace ai
{
    class GenericDruidNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericDruidNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(const char* name);
    };
}