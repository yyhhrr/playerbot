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
            creators["group invite"] = &WorldPacketTriggerContext::group_invite;
            creators["group set leader"] = &WorldPacketTriggerContext::group_set_leader;
            creators["not enough money"] = &WorldPacketTriggerContext::no_money;
        }

    private:
        static Trigger* gossip_hello(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "gossip hello"); }
        static Trigger* group_invite(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "group invite"); }
        static Trigger* group_set_leader(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "group set leader"); }
        static Trigger* no_money(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "not enough money"); }
    };
};