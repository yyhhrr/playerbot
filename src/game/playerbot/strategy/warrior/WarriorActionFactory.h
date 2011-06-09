#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class WarriorActionFactory : public ActionFactory
    {
    public:
        WarriorActionFactory(AiManagerRegistry* const ai);
    };
}