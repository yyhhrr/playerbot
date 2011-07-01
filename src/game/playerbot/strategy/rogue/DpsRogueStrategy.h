#pragma once

#include "../Strategy.h"

namespace ai
{
    class DpsRogueStrategy : public CombatStrategy
    {
    public:
        DpsRogueStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps"; }
        virtual NextAction** getDefaultActions();
    };
}
