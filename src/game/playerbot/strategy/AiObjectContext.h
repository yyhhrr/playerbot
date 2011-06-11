#pragma once

#include "../ai/AiManagerRegistryAware.h"
#include "Action.h"
#include "Strategy.h"
#include "Value.h"
#include "NamedObjectContext.h"

namespace ai
{
    class AiObjectContext : public AiManagerRegistryAware
    {
    public:
        AiObjectContext(AiManagerRegistry* const ai);
        virtual ~AiObjectContext() {}

    public:
        virtual Strategy* GetStrategy(const char* name) { return strategyContexts.GetObject(name, ai); }
        virtual Trigger* GetTrigger(const char* name) { return triggerContexts.GetObject(name, ai); }
        virtual Action* GetAction(const char* name) { return actionContexts.GetObject(name, ai); }
        
        template<class T>
        Value<T>* GetValue(const char* name) { return (Value<T>*)valueContexts.GetObject(name, ai); }

    public:
        void Update();

    protected:
        NamedObjectContextList<Strategy> strategyContexts;
        NamedObjectContextList<Action> actionContexts;
        NamedObjectContextList<Trigger> triggerContexts;
        NamedObjectContextList<UntypedValue> valueContexts;
    };
}