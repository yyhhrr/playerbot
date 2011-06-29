#pragma once

#include "../GenericNonCombatStrategy.h"

namespace ai
{
    class GenericDruidNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericDruidNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
