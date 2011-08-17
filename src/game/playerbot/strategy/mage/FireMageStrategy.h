#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FireMageStrategy : public GenericMageStrategy
    {
    public:
        FireMageStrategy(PlayerbotAI* ai) : GenericMageStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "fire"; }
        virtual NextAction** getDefaultActions();
    };
}
