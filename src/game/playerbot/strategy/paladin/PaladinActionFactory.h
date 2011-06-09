#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class PaladinActionFactory : public ActionFactory
    {
    public:
        PaladinActionFactory(AiManagerRegistry* const ai);
    };
}