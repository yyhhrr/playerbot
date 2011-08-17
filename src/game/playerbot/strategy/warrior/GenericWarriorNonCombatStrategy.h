#pragma once

#include "../GenericNonCombatStrategy.h"

namespace ai
{
    class GenericWarriorNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericWarriorNonCombatStrategy(PlayerbotAI* ai) : GenericNonCombatStrategy(ai) {}
        virtual string getName() { return "nc"; }
   };
}