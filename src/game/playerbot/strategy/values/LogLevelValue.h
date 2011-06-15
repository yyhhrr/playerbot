#pragma once
#include "../Value.h"
#include "../PlayerbotAIAware.h"

namespace ai
{
    class LogLevelValue : public ManualSetValue<LogLevel>
	{
	public:
        LogLevelValue(PlayerbotAI* ai) : 
            ManualSetValue<LogLevel>(ai, LOG_LVL_BASIC) {}    
	};
}
