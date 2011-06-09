#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class DruidActionFactory : public ActionFactory
    {
    public:
        DruidActionFactory(AiManagerRegistry* const ai);
    };
}