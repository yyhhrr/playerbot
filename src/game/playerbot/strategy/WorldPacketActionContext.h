#pragma once;

#include "GossipHelloAction.h"

namespace ai
{
    class WorldPacketActionContext : public NamedObjectContext<Action>
    {
    public:
        WorldPacketActionContext()
        {
            creators["gossip hello"] = &WorldPacketActionContext::gossip_hello;
        }

    private:
        static Action* gossip_hello(AiManagerRegistry* ai) { return new GossipHelloAction(ai); }

    };


};