#pragma once;

#include "GossipHelloAction.h"
#include "AcceptInvitationAction.h"

namespace ai
{
    class WorldPacketActionContext : public NamedObjectContext<Action>
    {
    public:
        WorldPacketActionContext()
        {
            creators["gossip hello"] = &WorldPacketActionContext::gossip_hello;
            creators["accept invitation"] = &WorldPacketActionContext::accept_invitation;
        }

    private:
        static Action* gossip_hello(AiManagerRegistry* ai) { return new GossipHelloAction(ai); }
        static Action* accept_invitation(AiManagerRegistry* ai) { return new AcceptInvitationAction(ai); }

    };


};