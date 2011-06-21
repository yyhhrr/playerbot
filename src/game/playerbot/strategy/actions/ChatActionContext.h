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
#include "UseItemAction.h"
#include "TellItemCountAction.h"
#include "RewardAction.h"
#include "BuyAction.h"
#include "SellAction.h"
#include "UnequipAction.h"
#include "EquipAction.h"
#include "TradeAction.h"
#include "ChangeTalentsAction.h"
#include "ListSpellsAction.h"
#include "ChangeStrategyAction.h"
#include "TrainerAction.h"
#include "ChangeChatAction.h"
#include "SetHomeAction.h"
#include "ResetAiAction.h"

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
            creators["use"] = &ChatActionContext::use;
            creators["item count"] = &ChatActionContext::item_count;
            creators["equip"] = &ChatActionContext::equip;
            creators["unequip"] = &ChatActionContext::unequip;
            creators["sell"] = &ChatActionContext::sell;
            creators["buy"] = &ChatActionContext::buy;
            creators["reward"] = &ChatActionContext::reward;
            creators["trade"] = &ChatActionContext::trade;
            creators["talents"] = &ChatActionContext::talents;
            creators["spells"] = &ChatActionContext::spells;
            creators["co"] = &ChatActionContext::co;
            creators["nc"] = &ChatActionContext::nc;
            creators["trainer"] = &ChatActionContext::trainer;
            creators["attack my target"] = &ChatActionContext::attack_my_target;
            creators["chat"] = &ChatActionContext::chat;
            creators["home"] = &ChatActionContext::home;
            creators["reset ai"] = &ChatActionContext::reset_ai;
        }

    private:
        static Action* home(PlayerbotAI* ai) { return new SetHomeAction(ai); }
        static Action* chat(PlayerbotAI* ai) { return new ChangeChatAction(ai); }
        static Action* attack_my_target(PlayerbotAI* ai) { return new AttackMyTargetAction(ai); }
        static Action* trainer(PlayerbotAI* ai) { return new TrainerAction(ai); }
        static Action* co(PlayerbotAI* ai) { return new ChangeCombatStrategyAction(ai); }
        static Action* nc(PlayerbotAI* ai) { return new ChangeNonCombatStrategyAction(ai); }
        static Action* spells(PlayerbotAI* ai) { return new ListSpellsAction(ai); }
        static Action* talents(PlayerbotAI* ai) { return new ChangeTalentsAction(ai); }

        static Action* equip(PlayerbotAI* ai) { return new EquipAction(ai); }
        static Action* unequip(PlayerbotAI* ai) { return new UnequipAction(ai); }
        static Action* sell(PlayerbotAI* ai) { return new SellAction(ai); }
        static Action* buy(PlayerbotAI* ai) { return new BuyAction(ai); }
        static Action* reward(PlayerbotAI* ai) { return new RewardAction(ai); }
        static Action* trade(PlayerbotAI* ai) { return new TradeAction(ai); }

        static Action* item_count(PlayerbotAI* ai) { return new TellItemCountAction(ai); }
        static Action* use(PlayerbotAI* ai) { return new UseItemAction(ai); }
        static Action* repair(PlayerbotAI* ai) { return new RepairAllAction(ai); }
        static Action* taxi(PlayerbotAI* ai) { return new TaxiAction(ai); }
        static Action* teleport(PlayerbotAI* ai) { return new TeleportAction(ai); }
        static Action* release(PlayerbotAI* ai) { return new ReleaseSpiritAction(ai); }
        static Action* query_item_usage(PlayerbotAI* ai) { return new QueryItemUsageAction(ai); }
        static Action* query_quest(PlayerbotAI* ai) { return new QueryQuestAction(ai); }
        static Action* query_quest_item(PlayerbotAI* ai) { return new QueryQuestItemAction(ai); }
        static Action* drop(PlayerbotAI* ai) { return new DropQuestAction(ai); }
        static Action* stats(PlayerbotAI* ai) { return new StatsAction(ai); }
        static Action* quests(PlayerbotAI* ai) { return new ListQuestsAction(ai); }
        static Action* leave(PlayerbotAI* ai) { return new LeaveGroupAction(ai); }
        static Action* reputation(PlayerbotAI* ai) { return new TellReputationAction(ai); }
        static Action* log(PlayerbotAI* ai) { return new LogLevelAction(ai); }
        static Action* los(PlayerbotAI* ai) { return new TellLosAction(ai); }
        static Action* ll(PlayerbotAI* ai) { return new LootStrategyAction(ai); }
        static Action* add_all_loot(PlayerbotAI* ai) { return new AddAllLootAction(ai); }
        static Action* reset_ai(PlayerbotAI* ai) { return new ResetAiAction(ai); }
    };


};
