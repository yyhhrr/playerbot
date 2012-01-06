#pragma once
#include "Action.h"

namespace ai 
{
    class Multiplier : public AiObject
    {
    public:
        Multiplier(PlayerbotAI* ai) : AiObject(ai) {}
        virtual ~Multiplier() {}

    public:
        virtual float GetValue(Action* action) { return 1.0f; }
    };

}
