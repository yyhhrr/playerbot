#pragma once

#include "../GenericNonCombatStrategy.h"

namespace ai
{
    class GenericHunterNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericHunterNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
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
