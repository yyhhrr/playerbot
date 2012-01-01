#pragma once

#include "../generic/GenericNonCombatStrategy.h"

namespace ai
{
    class GenericWarlockNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericWarlockNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
