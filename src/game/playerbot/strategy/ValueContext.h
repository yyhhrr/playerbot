#pragma once;

#include "NearestGameObjects.h"
#include "LogLevelValue.h"

namespace ai
{
    class ValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        ValueContext()
        {
            creators["nearest game objects"] = &ValueContext::nearest_game_objects;
            creators["log level"] = &ValueContext::log_level;
        }

    private:
        static UntypedValue* nearest_game_objects(AiManagerRegistry* ai) { return new NearestGameObjects(ai); }
        static UntypedValue* log_level(AiManagerRegistry* ai) { return new LogLevelValue(ai); }
    };
};