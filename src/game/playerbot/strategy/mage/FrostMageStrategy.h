#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FrostMageStrategy : public GenericMageStrategy
    {
    public:
        FrostMageStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "frost"; }
        virtual NextAction** getDefaultActions();
    };
}
