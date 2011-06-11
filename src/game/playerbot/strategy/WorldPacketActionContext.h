#pragma once;

#include "GossipHelloAction.h"
#include "AcceptInvitationAction.h"
#include "PassLeadershipToMasterAction.h"

namespace ai
{
    class WorldPacketActionContext : public NamedObjectContext<Action>
    {
    public:
        WorldPacketActionContext()
        {
            creators["gossip hello"] = &WorldPacketActionContext::gossip_hello;
            creators["accept invitation"] = &WorldPacketActionContext::accept_invitation;
            creators["pass leadership to master"] = &WorldPacketActionContext::pass_leadership_to_master;
        }

    private:
        static Action* gossip_hello(AiManagerRegistry* ai) { return new GossipHelloAction(ai); }
        static Action* accept_invitation(AiManagerRegistry* ai) { return new AcceptInvitationAction(ai); }
        static Action* pass_leadership_to_master(AiManagerRegistry* ai) { return new PassLeadershipToMasterAction(ai); }

    };


};