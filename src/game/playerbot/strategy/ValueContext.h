#pragma once;

#include "NearestGameObjects.h"
#include "LogLevelValue.h"
#include "NearestNpcsValue.h"
#include "PossibleTargetsValue.h"
#include "NearestCorpsesValue.h"

namespace ai
{
    class ValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        ValueContext()
        {
            creators["nearest game objects"] = &ValueContext::nearest_game_objects;
            creators["nearest npcs"] = &ValueContext::nearest_npcs;
            creators["possible targets"] = &ValueContext::possible_targets;
            creators["nearest corpses"] = &ValueContext::nearest_corpses;
            creators["log level"] = &ValueContext::log_level;
        }

    private:
        static UntypedValue* nearest_game_objects(AiManagerRegistry* ai) { return new NearestGameObjects(ai); }
        static UntypedValue* log_level(AiManagerRegistry* ai) { return new LogLevelValue(ai); }
        static UntypedValue* nearest_npcs(AiManagerRegistry* ai) { return new NearestNpcsValue(ai); }
        static UntypedValue* nearest_corpses(AiManagerRegistry* ai) { return new NearestCorpsesValue(ai); }
        static UntypedValue* possible_targets(AiManagerRegistry* ai) { return new PossibleTargetsValue(ai); }
    };
};