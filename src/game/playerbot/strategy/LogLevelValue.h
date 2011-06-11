#pragma once
#include "Value.h"
#include "../ai/AiManagerRegistryAware.h"

namespace ai
{
    class LogLevelValue : public ManualSetValue<LogLevel>
	{
	public:
        LogLevelValue(AiManagerRegistry* const ai) : 
            ManualSetValue<LogLevel>(ai, LOG_LVL_BASIC) {}    
	};
}
