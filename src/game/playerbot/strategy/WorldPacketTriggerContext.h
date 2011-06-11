#pragma once;

#include "WorldPacketTrigger.h"

namespace ai
{
    class WorldPacketTriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        WorldPacketTriggerContext()
        {
            creators["gossip hello"] = &WorldPacketTriggerContext::gossip_hello;
        }

    private:
        static Trigger* gossip_hello(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "gossip hello"); }
    };
};