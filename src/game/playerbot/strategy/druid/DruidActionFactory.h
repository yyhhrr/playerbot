#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class DruidActionFactory : public ActionFactory
    {
    public:
        DruidActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
        virtual Trigger* createTrigger(const char* name);
        virtual Action* createAction(const char* name);
    };
}