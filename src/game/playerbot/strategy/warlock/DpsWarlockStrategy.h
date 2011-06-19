#pragma once

#include "GenericWarlockStrategy.h"

namespace ai
{
    class DpsWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        DpsWarlockStrategy(PlayerbotAI* ai) : GenericWarlockStrategy(ai) {}
        virtual string getName() { return "dps"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
    };
}