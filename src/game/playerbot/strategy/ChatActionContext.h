#pragma once;

namespace ai
{
    class ChatActionContext : public NamedObjectContext<Action>
    {
    public:
        ChatActionContext()
        {
            creators["stats"] = &ChatActionContext::stats;
            creators["quests"] = &ChatActionContext::quests;
        }

    private:
        static Action* stats(AiManagerRegistry* ai) { return new StatsAction(ai); }
        static Action* quests(AiManagerRegistry* ai) { return new ListQuestsAction(ai); }

    };


};