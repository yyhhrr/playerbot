#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class WarlockActionFactory : public ActionFactory
    {
    public:
        WarlockActionFactory(AiManagerRegistry* const ai);
    };
}