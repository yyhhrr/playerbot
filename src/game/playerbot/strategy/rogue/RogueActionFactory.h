#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class RogueActionFactory : public ActionFactory
    {
    public:
        RogueActionFactory(AiManagerRegistry* const ai);
    };
}