#pragma once;

#include "AttackersValue.h"
#include "AttackerCountValues.h"

namespace ai
{
    class SharedValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        SharedValueContext()
        {
            creators["balance"] = &SharedValueContext::balance;
            creators["attackers"] = &SharedValueContext::attackers;
        }
    
    public:
        virtual bool IsShared() { return true; }

    private:
        static UntypedValue* balance(AiManagerRegistry* ai) { return new BalancePercentValue(ai); }
        static UntypedValue* attackers(AiManagerRegistry* ai) { return new AttackersValue(ai); }
    };
};