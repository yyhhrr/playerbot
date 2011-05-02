#pragma once

#include "GenericShamanStrategy.h"

namespace ai
{
    class MeleeShamanStrategy : public GenericShamanStrategy
    {
    public:
        MeleeShamanStrategy(AiManagerRegistry* const ai) : GenericShamanStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
        virtual const char* getName() { return "melee"; }
        virtual ActionNode* createAction(const char* name);

    };
}
