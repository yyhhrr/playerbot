#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class PriestActionFactory : public ActionFactory
    {
    public:
        PriestActionFactory(AiManagerRegistry* const ai);
    };
}