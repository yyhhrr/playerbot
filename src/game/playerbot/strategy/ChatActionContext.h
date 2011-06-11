#pragma once;

#include "ListQuestsActions.h"
#include "StatsAction.h"
#include "LeaveGroupAction.h"
#include "TellReputationAction.h"
#include "LogLevelAction.h"

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
            creators["log"] = &ChatActionContext::log;
        }

    private:
        static Action* stats(AiManagerRegistry* ai) { return new StatsAction(ai); }
        static Action* quests(AiManagerRegistry* ai) { return new ListQuestsAction(ai); }
        static Action* leave(AiManagerRegistry* ai) { return new LeaveGroupAction(ai); }
        static Action* reputation(AiManagerRegistry* ai) { return new TellReputationAction(ai); }
        static Action* log(AiManagerRegistry* ai) { return new LogLevelAction(ai); }

    };


};