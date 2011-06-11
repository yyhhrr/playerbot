#pragma once

#include "../ai/AiManagerRegistryAware.h"
#include "Action.h"
#include "Strategy.h"
#include "NamedObjectContext.h"

namespace ai
{
    class AiObjectContext : public AiManagerRegistryAware
    {
    public:
        AiObjectContext(AiManagerRegistry* const ai);
        virtual ~AiObjectContext() {}

    public:
        Strategy* GetStrategy(const char* name) { return strategyContexts.GetObject(name, ai); }
        Trigger* GetTrigger(const char* name) { return triggerContexts.GetObject(name, ai); }
        Action* GetAction(const char* name) { return actionContexts.GetObject(name, ai); }

    protected:
        NamedObjectContextList<Strategy> strategyContexts;
        NamedObjectContextList<Action> actionContexts;
        NamedObjectContextList<Trigger> triggerContexts;
    };
}