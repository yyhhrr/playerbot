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
            creators["not enough reputation"] = &WorldPacketTriggerContext::no_reputation;
            creators["cannot equip"] = &WorldPacketTriggerContext::cannot_equip;
            creators["use game object"] = &WorldPacketTriggerContext::use_game_object;
            creators["complete quest"] = &WorldPacketTriggerContext::complete_quest;
            creators["accept quest"] = &WorldPacketTriggerContext::accept_quest;
            creators["quest share"] = &WorldPacketTriggerContext::quest_share;
            creators["loot roll"] = &WorldPacketTriggerContext::loot_roll;
            creators["resurrect request"] = &WorldPacketTriggerContext::resurrect_request;
            creators["area trigger"] = &WorldPacketTriggerContext::area_trigger;
            creators["check mount state"] = &WorldPacketTriggerContext::check_mount_state;
            creators["activate taxi"] = &WorldPacketTriggerContext::taxi;
        }

    private:
        static Trigger* cannot_equip(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "cannot equip"); }
        static Trigger* check_mount_state(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "check mount state"); }
        static Trigger* area_trigger(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "area trigger"); }
        static Trigger* resurrect_request(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "resurrect request"); }
        static Trigger* gossip_hello(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "gossip hello"); }
        static Trigger* group_invite(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "group invite"); }
        static Trigger* group_set_leader(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "group set leader"); }
        static Trigger* no_money(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "not enough money"); }
        static Trigger* no_reputation(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "not enough reputation"); }
        static Trigger* use_game_object(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "use game object"); }
        static Trigger* complete_quest(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "complete quest"); }
        static Trigger* accept_quest(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "accept quest"); }
        static Trigger* quest_share(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "quest share"); }
        static Trigger* loot_roll(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "loot roll"); }
        static Trigger* taxi(AiManagerRegistry* ai) { return new WorldPacketTrigger(ai, "activate taxi"); }
    };
};