#pragma once

#include "../ActionFactory.h"

namespace ai
{
    class ShamanActionFactory : public ActionFactory
    {
    public:
        ShamanActionFactory(AiManagerRegistry* const ai);
    };
}
