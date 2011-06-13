#pragma once;

#include "GossipHelloAction.h"
#include "AcceptInvitationAction.h"
#include "PassLeadershipToMasterAction.h"
#include "TellMasterAction.h"
#include "TurnInQuestAction.h"
#include "AcceptQuestAction.h"
#include "LootRollAction.h"
#include "ReviveFromCorpseAction.h"
#include "AcceptResurrectAction.h"
#include "UseMeetingStoneAction.h"
#include "AreaTriggerAction.h"
#include "CheckMountStateAction.h"
#include "RememberTaxiAction.h"

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
            creators["turn in quest"] = &WorldPacketActionContext::turn_in_quest;
            creators["accept quest"] = &WorldPacketActionContext::accept_quest;
            creators["accept quest share"] = &WorldPacketActionContext::accept_quest_share;
            creators["loot roll"] = &WorldPacketActionContext::loot_roll;
            creators["revive from corpse"] = &WorldPacketActionContext::revive_from_corpse;
            creators["accept resurrect"] = &WorldPacketActionContext::accept_resurrect;
            creators["use meeting stone"] = &WorldPacketActionContext::use_meeting_stone;
            creators["area trigger"] = &WorldPacketActionContext::area_trigger;
            creators["check mount state"] = &WorldPacketActionContext::check_mount_state;
            creators["remember taxi"] = &WorldPacketActionContext::remember_taxi;
        }

    private:
        static Action* remember_taxi(AiManagerRegistry* ai) { return new RememberTaxiAction(ai); }
        static Action* check_mount_state(AiManagerRegistry* ai) { return new CheckMountStateAction(ai); }
        static Action* area_trigger(AiManagerRegistry* ai) { return new AreaTriggerAction(ai); }
        static Action* use_meeting_stone(AiManagerRegistry* ai) { return new UseMeetingStoneAction(ai); }
        static Action* accept_resurrect(AiManagerRegistry* ai) { return new AcceptResurrectAction(ai); }
        static Action* revive_from_corpse(AiManagerRegistry* ai) { return new ReviveFromCorpseAction(ai); }
        static Action* gossip_hello(AiManagerRegistry* ai) { return new GossipHelloAction(ai); }
        static Action* accept_invitation(AiManagerRegistry* ai) { return new AcceptInvitationAction(ai); }
        static Action* pass_leadership_to_master(AiManagerRegistry* ai) { return new PassLeadershipToMasterAction(ai); }
        static Action* tell_not_enough_money(AiManagerRegistry* ai) { return new TellMasterAction(ai, "Not enough money"); }
        static Action* tell_not_enough_reputation(AiManagerRegistry* ai) { return new TellMasterAction(ai, "Not enough reputation"); }
        static Action* turn_in_quest(AiManagerRegistry* ai) { return new TurnInQuestAction(ai); }
        static Action* accept_quest(AiManagerRegistry* ai) { return new AcceptQuestAction(ai); }
        static Action* accept_quest_share(AiManagerRegistry* ai) { return new AcceptQuestShareAction(ai); }
        static Action* loot_roll(AiManagerRegistry* ai) { return new LootRollAction(ai); }
    };


};