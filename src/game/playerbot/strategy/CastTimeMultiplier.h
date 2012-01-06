#pragma once
#include "Action.h"
#include "Multiplier.h"

namespace ai 
{
    class CastTimeMultiplier : public Multiplier
    {
    public:
        CastTimeMultiplier(PlayerbotAI* ai) : Multiplier(ai) {}

    public:
        virtual float GetValue(Action* action);
    };

}
