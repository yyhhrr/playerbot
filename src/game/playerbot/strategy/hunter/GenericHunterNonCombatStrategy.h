#pragma once

#include "../GenericNonCombatStrategy.h"

namespace ai
{
    class GenericHunterNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericHunterNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
    };

    class HunterBuffSpeedNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        HunterBuffSpeedNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "bspeed"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}