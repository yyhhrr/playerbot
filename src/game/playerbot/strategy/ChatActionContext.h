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
#include "LootStrategyAction.h"
#include "AddLootAction.h"
#include "ReleaseSpiritAction.h"
#include "TeleportAction.h"
#include "TaxiAction.h"
#include "RepairAllAction.h"

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
            creators["ll"] = &ChatActionContext::ll;
            creators["add all loot"] = &ChatActionContext::add_all_loot;
            creators["release"] = &ChatActionContext::release;
            creators["teleport"] = &ChatActionContext::teleport;
            creators["taxi"] = &ChatActionContext::taxi;
            creators["repair"] = &ChatActionContext::repair;
        }

    private:
        static Action* repair(AiManagerRegistry* ai) { return new RepairAllAction(ai); }
        static Action* taxi(AiManagerRegistry* ai) { return new TaxiAction(ai); }
        static Action* teleport(AiManagerRegistry* ai) { return new TeleportAction(ai); }
        static Action* release(AiManagerRegistry* ai) { return new ReleaseSpiritAction(ai); }
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
        static Action* ll(AiManagerRegistry* ai) { return new LootStrategyAction(ai); }
        static Action* add_all_loot(AiManagerRegistry* ai) { return new AddAllLootAction(ai); }
    };


};