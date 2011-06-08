#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class HunterActionFactory : public ActionFactory
    {
    public:
        HunterActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}

    public:
        virtual Strategy* createStrategy(const char* name);
        virtual Trigger* createTrigger(const char* name);
        virtual Action* createAction(const char* name);
    };
}