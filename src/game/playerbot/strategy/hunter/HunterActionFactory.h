#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class HunterActionFactory : public ActionFactory
    {
    public:
        HunterActionFactory(AiManagerRegistry* const ai);
    };
}