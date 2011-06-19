#pragma once

#include "GenericShamanStrategy.h"

namespace ai
{
    class MeleeShamanStrategy : public GenericShamanStrategy
    {
    public:
        MeleeShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
        virtual string getName() { return "melee"; }
        virtual ActionNode* GetAction(string name);
		virtual string GetIncompatibleStrategies() { return "-heal"; }
    };
}
