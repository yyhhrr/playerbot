#pragma once

#include "../ai/AiManagerRegistryAware.h"
#include "Action.h"
#include "Strategy.h"
#include "NamedObjectFactory.h"

#define CREATE_ACTION_RULE(actioname, clazz) \
    if (!strcmp(actioname, name)) \
        return new clazz(ai);


namespace ai
{
    class ActionFactory : public AiManagerRegistryAware
    {
    public:
        ActionFactory(AiManagerRegistry* const ai);
        virtual ~ActionFactory();

    public:
        virtual Strategy* createStrategy(const char* name);
        virtual Trigger* createTrigger(const char* name);
        virtual Action* createAction(const char* name);

    protected:
        list<NamedObjectFactory<Strategy>*> strategyFactories;
        list<NamedObjectFactory<Action>*> actionFactories;
        list<NamedObjectFactory<Trigger>*> triggerFactories;
    };
}