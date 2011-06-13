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
        virtual UntypedValue* GetUntypedValue(const char* name) { return valueContexts.GetObject(name, ai); }
        
        template<class T>
        Value<T>* GetValue(const char* name)
        {
            return dynamic_cast<Value<T>*>(GetUntypedValue(name)); 
        }

        template<class T>
        Value<T>* GetValue(const char* name, const char* param)
        {
            return GetValue<T>((string(name) + "::" + param).c_str()); 
        }

        template<class T>
        Value<T>* GetValue(const char* name, uint32 param)
        {
            char buffer[64]; itoa(param, buffer, 10);
            return GetValue<T>(name, buffer); 
        }

    public:
        virtual void Update();
        virtual void AddShared(NamedObjectContext<UntypedValue>* sharedValues)
        {
            valueContexts.Add(sharedValues);
        }

    protected:
        NamedObjectContextList<Strategy> strategyContexts;
        NamedObjectContextList<Action> actionContexts;
        NamedObjectContextList<Trigger> triggerContexts;
        NamedObjectContextList<UntypedValue> valueContexts;
    };
}