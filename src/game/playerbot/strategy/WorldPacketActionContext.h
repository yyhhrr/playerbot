#pragma once;

#include "GossipHelloAction.h"
#include "AcceptInvitationAction.h"
#include "PassLeadershipToMasterAction.h"
#include "TellMasterAction.h"
#include "DropQuestAction.h"

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
            creators["tell not enough money"] = &WorldPacketActionContext::tell_not_enough_money;
            creators["tell not enough reputation"] = &WorldPacketActionContext::tell_not_enough_reputation;
            creators["drop"] = &WorldPacketActionContext::drop;
        }

    private:
        static Action* gossip_hello(AiManagerRegistry* ai) { return new GossipHelloAction(ai); }
        static Action* accept_invitation(AiManagerRegistry* ai) { return new AcceptInvitationAction(ai); }
        static Action* pass_leadership_to_master(AiManagerRegistry* ai) { return new PassLeadershipToMasterAction(ai); }
        static Action* tell_not_enough_money(AiManagerRegistry* ai) { return new TellMasterAction(ai, "Not enough money"); }
        static Action* tell_not_enough_reputation(AiManagerRegistry* ai) { return new TellMasterAction(ai, "Not enough reputation"); }
        static Action* drop(AiManagerRegistry* ai) { return new DropQuestAction(ai); }
    };


};