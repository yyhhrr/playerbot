#pragma once;

namespace ai
{
    class ChatTriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        ChatTriggerContext()
        {
            creators["quests"] = &ChatTriggerContext::quests;
            creators["stats"] = &ChatTriggerContext::stats;
        }

    private:
        static Trigger* quests(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "quests"); }
        static Trigger* stats(AiManagerRegistry* ai) { return new ChatCommandTrigger(ai, "stats"); }

    };
};