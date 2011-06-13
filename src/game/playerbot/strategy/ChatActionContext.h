#pragma once;

#include "ListQuestsActions.h"
#include "StatsAction.h"
#include "LeaveGroupAction.h"
#include "TellReputationAction.h"
#include "LogLevelAction.h"
#include "TellLosAction.h"
#include "DropQuestAction.h"
#include "QueryQuestAction.h"
#include "QueryQuestItemAction.h"
#include "QueryItemUsageAction.h"

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
            creators["los"] = &ChatActionContext::los;
            creators["drop"] = &ChatActionContext::drop;
            creators["query quest"] = &ChatActionContext::query_quest;
            creators["query quest item"] = &ChatActionContext::query_quest_item;
            creators["query item usage"] = &ChatActionContext::query_item_usage;
        }

    private:
        static Action* query_item_usage(AiManagerRegistry* ai) { return new QueryItemUsageAction(ai); }
        static Action* query_quest(AiManagerRegistry* ai) { return new QueryQuestAction(ai); }
        static Action* query_quest_item(AiManagerRegistry* ai) { return new QueryQuestItemAction(ai); }
        static Action* drop(AiManagerRegistry* ai) { return new DropQuestAction(ai); }
        static Action* stats(AiManagerRegistry* ai) { return new StatsAction(ai); }
        static Action* quests(AiManagerRegistry* ai) { return new ListQuestsAction(ai); }
        static Action* leave(AiManagerRegistry* ai) { return new LeaveGroupAction(ai); }
        static Action* reputation(AiManagerRegistry* ai) { return new TellReputationAction(ai); }
        static Action* log(AiManagerRegistry* ai) { return new LogLevelAction(ai); }
        static Action* los(AiManagerRegistry* ai) { return new TellLosAction(ai); }

    };


};