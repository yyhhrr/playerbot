#pragma once

#include "../Strategy.h"

namespace ai
{
    class GenericPriestStrategy : public CombatStrategy
    {
    public:
        GenericPriestStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);

    };
}
