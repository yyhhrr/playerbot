#pragma once

#include "../Strategy.h"
#include "PaladinAiObjectContext.h"
#include "../generic/CombatStrategy.h"

namespace ai
{
    class GenericPaladinStrategy : public CombatStrategy
    {
    public:
        GenericPaladinStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "paladin"; }
    };
}
