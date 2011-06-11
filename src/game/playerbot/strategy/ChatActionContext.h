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
            creators["leave"] = &ChatActionContext::leave;
            creators["reputation"] = &ChatActionContext::reputation;
        }

    private:
        static Action* stats(AiManagerRegistry* ai) { return new StatsAction(ai); }
        static Action* quests(AiManagerRegistry* ai) { return new ListQuestsAction(ai); }
        static Action* leave(AiManagerRegistry* ai) { return new LeaveGroupAction(ai); }
        static Action* reputation(AiManagerRegistry* ai) { return new TellReputationAction(ai); }

    };


};