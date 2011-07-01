#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class GenericMageNonCombatStrategy : public GenericMageStrategy
    {
    public:
        GenericMageNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
