#pragma once;

#include "NearestGameObjects.h"

namespace ai
{
    class ValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        ValueContext()
        {
            creators["nearest game objects"] = &ValueContext::nearest_game_objects;
        }

    private:
        static UntypedValue* nearest_game_objects(AiManagerRegistry* ai) { return new NearestGameObjects(ai); }
    };
};