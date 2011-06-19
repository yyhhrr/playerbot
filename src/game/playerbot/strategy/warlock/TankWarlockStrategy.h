#pragma once

#include "GenericWarlockStrategy.h"

namespace ai
{
    class TankWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        TankWarlockStrategy(PlayerbotAI* ai) : GenericWarlockStrategy(ai) {}
        virtual string getName() { return "tank"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
    };
}