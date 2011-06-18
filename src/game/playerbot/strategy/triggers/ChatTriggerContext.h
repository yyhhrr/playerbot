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
            creators["e"] = &ChatTriggerContext::equip;
            creators["ue"] = &ChatTriggerContext::uneqip;
            creators["s"] = &ChatTriggerContext::sell;
            creators["b"] = &ChatTriggerContext::buy;
            creators["r"] = &ChatTriggerContext::reward;
            creators["t"] = &ChatTriggerContext::trade;
            creators["nt"] = &ChatTriggerContext::nontrade;
            creators["talents"] = &ChatTriggerContext::talents;
            creators["spells"] = &ChatTriggerContext::spells;
            creators["co"] = &ChatTriggerContext::co;
            creators["nc"] = &ChatTriggerContext::nc;
            creators["trainer"] = &ChatTriggerContext::trainer;
            creators["attack"] = &ChatTriggerContext::attack;
        }

    private:
        static Trigger* attack(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "attack"); }
        static Trigger* trainer(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "trainer"); }
        static Trigger* co(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "co"); }
        static Trigger* nc(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "nc"); }
        static Trigger* spells(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "spells"); }
        static Trigger* talents(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "talents"); }
        static Trigger* equip(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "e"); }
        static Trigger* uneqip(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "ue"); }
        static Trigger* sell(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "s"); }
        static Trigger* buy(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "b"); }
        static Trigger* reward(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "r"); }
        static Trigger* trade(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "t"); }
        static Trigger* nontrade(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "nt"); }
        
        static Trigger* item_count(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "c"); }
        static Trigger* use(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "use"); }
        static Trigger* repair(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "repair"); }
        static Trigger* taxi(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "taxi"); }
        static Trigger* teleport(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "teleport"); }
        static Trigger* q(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "q"); }
        static Trigger* ll(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "ll"); }
        static Trigger* drop(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "drop"); }
        static Trigger* quests(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "quests"); }
        static Trigger* stats(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "stats"); }
        static Trigger* leave(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "leave"); }
        static Trigger* reputation(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "reputation"); }
        static Trigger* log(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "log"); }
        static Trigger* los(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "los"); }
        static Trigger* loot_all(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "add all loot"); }
        static Trigger* release(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "release"); }
    };
};