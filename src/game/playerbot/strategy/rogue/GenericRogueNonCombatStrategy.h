#pragma once

#include "../generic/GenericNonCombatStrategy.h"

namespace ai
{
    class GenericRogueNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericRogueNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}