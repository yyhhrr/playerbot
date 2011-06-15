#pragma once

#include "Strategy.h"

namespace ai
{
    class RacialsStrategy : public Strategy
    {
    public:
        RacialsStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual const char* getName() { return "racials"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(const char* name);
    };

}