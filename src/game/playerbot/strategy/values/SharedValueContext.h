#pragma once;

#include "AttackersValue.h"
#include "AttackerCountValues.h"

namespace ai
{
    class SharedValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        SharedValueContext() : NamedObjectContext<UntypedValue>(true)
        {
            creators["balance"] = &SharedValueContext::balance;
            creators["attackers"] = &SharedValueContext::attackers;
        }
    
    private:
        static UntypedValue* balance(PlayerbotAI* ai) { return new BalancePercentValue(ai); }
        static UntypedValue* attackers(PlayerbotAI* ai) { return new AttackersValue(ai); }
    };
};