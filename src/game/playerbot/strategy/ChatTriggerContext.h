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
        }

    private:
        static Trigger* quests(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "quests"); }
        static Trigger* stats(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "stats"); }
        static Trigger* leave(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "leave"); }
        static Trigger* reputation(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "reputation"); }
        static Trigger* log(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "log"); }
        static Trigger* los(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "los"); }
    };
};