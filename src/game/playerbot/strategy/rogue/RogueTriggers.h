#pragma once
#include "../GenericTriggers.h"

namespace ai
{

    class KickInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        KickInterruptSpellTrigger(AiManagerRegistry* const ai) : InterruptSpellTrigger(ai, "kick") {}
    };

}
