#pragma once;

#include "ChatCommandTrigger.h"

namespace ai
{
    class ChatTriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        ChatTriggerContext()
        {
            creators["quests"] = &ChatTriggerContext::quests;
            creators["stats"] = &ChatTriggerContext::stats;
            creators["leave"] = &ChatTriggerContext::leave;
            creators["rep"] = &ChatTriggerContext::reputation;
            creators["reputation"] = &ChatTriggerContext::reputation;
            creators["log"] = &ChatTriggerContext::log;
            creators["los"] = &ChatTriggerContext::los;
            creators["drop"] = &ChatTriggerContext::drop;
            creators["q"] = &ChatTriggerContext::q;
            creators["ll"] = &ChatTriggerContext::ll;
            creators["loot all"] = &ChatTriggerContext::loot_all;
            creators["add all loot"] = &ChatTriggerContext::loot_all;
            creators["release"] = &ChatTriggerContext::release;
            creators["teleport"] = &ChatTriggerContext::teleport;
            creators["taxi"] = &ChatTriggerContext::taxi;
            creators["repair"] = &ChatTriggerContext::repair;
            creators["u"] = &ChatTriggerContext::use;
            creators["use"] = &ChatTriggerContext::use;
            creators["c"] = &ChatTriggerContext::item_count;
        }

    private:
        static Trigger* item_count(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "c"); }
        static Trigger* use(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "use"); }
        static Trigger* repair(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "repair"); }
        static Trigger* taxi(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "taxi"); }
        static Trigger* teleport(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "teleport"); }
        static Trigger* q(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "q"); }
        static Trigger* ll(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "ll"); }
        static Trigger* drop(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "drop"); }
        static Trigger* quests(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "quests"); }
        static Trigger* stats(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "stats"); }
        static Trigger* leave(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "leave"); }
        static Trigger* reputation(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "reputation"); }
        static Trigger* log(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "log"); }
        static Trigger* los(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "los"); }
        static Trigger* loot_all(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "add all loot"); }
        static Trigger* release(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "release"); }
    };
};