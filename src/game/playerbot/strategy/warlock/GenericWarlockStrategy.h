#pragma once

#include "../Strategy.h"

namespace ai
{
    class GenericWarlockStrategy : public CombatStrategy
    {
    public:
        GenericWarlockStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        virtual string getName() { return "warlock"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* GetAction(string name);
        virtual NextAction** getDefaultActions();
    };
}