#pragma once;

#include "GenericActions.h"
#include "NonCombatActions.h"
#include "EmoteAction.h"
#include "AddLootAction.h"
#include "LootAction.h"
#include "AddLootAction.h"
#include "StayActions.h"
#include "FollowActions.h"

namespace ai
{
    class ActionContext : public NamedObjectContext<Action>
    {
    public:
        ActionContext()
        {
            creators["attack"] = &ActionContext::melee;
            creators["melee"] = &ActionContext::melee;
            creators["reach spell"] = &ActionContext::ReachSpell;
            creators["reach melee"] = &ActionContext::ReachMelee;
            creators["flee"] = &ActionContext::flee;
            creators["gift of the naaru"] = &ActionContext::gift_of_the_naaru;
            creators["shoot"] = &ActionContext::shoot;
            creators["lifeblood"] = &ActionContext::lifeblood;
            creators["arcane torrent"] = &ActionContext::arcane_torrent;
            creators["end pull"] = &ActionContext::end_pull;
            creators["healthstone"] = &ActionContext::healthstone;
            creators["healing potion"] = &ActionContext::healing_potion;
            creators["mana potion"] = &ActionContext::mana_potion;
            creators["food"] = &ActionContext::food;
            creators["drink"] = &ActionContext::drink;
            creators["tank assist"] = &ActionContext::tank_assist;
            creators["dps assist"] = &ActionContext::dps_assist;
            creators["loot"] = &ActionContext::loot;
            creators["add loot"] = &ActionContext::add_loot;
            creators["add all loot"] = &ActionContext::add_all_loot;
            creators["shoot"] = &ActionContext::shoot;
            creators["follow line"] = &ActionContext::follow_line;
            creators["follow"] = &ActionContext::follow_master;
            creators["follow master"] = &ActionContext::follow_master;
            creators["goaway"] = &ActionContext::goaway;
            creators["stay"] = &ActionContext::stay;
            creators["stay circle"] = &ActionContext::stay_circle;
            creators["stay line"] = &ActionContext::stay_line;
            creators["stay combat"] = &ActionContext::stay_combat;
            creators["attack anything"] = &ActionContext::attack_anything;
            creators["emote"] = &ActionContext::emote;
        }

    private:
        static Action* shoot(PlayerbotAI* ai) { return new CastShootAction(ai); }
        static Action* melee(PlayerbotAI* ai) { return new MeleeAction(ai); }
        static Action* ReachSpell(PlayerbotAI* ai) { return new ReachSpellAction(ai); }
        static Action* ReachMelee(PlayerbotAI* ai) { return new ReachMeleeAction(ai); }
        static Action* flee(PlayerbotAI* ai) { return new FleeAction(ai); }
        static Action* gift_of_the_naaru(PlayerbotAI* ai) { return new CastGiftOfTheNaaruAction(ai); }
        static Action* lifeblood(PlayerbotAI* ai) { return new CastLifeBloodAction(ai); }
        static Action* arcane_torrent(PlayerbotAI* ai) { return new CastArcaneTorrentAction(ai); }
        static Action* end_pull(PlayerbotAI* ai) { return new ChangeCombatStrategyAction(ai, "-pull"); }

        static Action* emote(PlayerbotAI* ai) { return new EmoteAction(ai, 0); }
        static Action* attack_anything(PlayerbotAI* ai) { return new AttackAnythingAction(ai); }
        static Action* stay_combat(PlayerbotAI* ai) { return new StayCombatAction(ai); }
        static Action* stay_line(PlayerbotAI* ai) { return new StayLineAction(ai); }
        static Action* stay_circle(PlayerbotAI* ai) { return new StayCircleAction(ai); }
        static Action* stay(PlayerbotAI* ai) { return new StayAction(ai); }
        static Action* goaway(PlayerbotAI* ai) { return new GoAwayAction(ai); }
        static Action* follow_master(PlayerbotAI* ai) { return new FollowMasterAction(ai); }
        static Action* follow_line(PlayerbotAI* ai) { return new FollowLineAction(ai); }
        static Action* add_loot(PlayerbotAI* ai) { return new AddLootAction(ai); }
        static Action* add_all_loot(PlayerbotAI* ai) { return new AddAllLootAction(ai); }
        static Action* loot(PlayerbotAI* ai) { return new LootAction(ai); }
        static Action* dps_assist(PlayerbotAI* ai) { return new DpsAssistAction(ai); }
        static Action* tank_assist(PlayerbotAI* ai) { return new TankAssistAction(ai); }
        static Action* drink(PlayerbotAI* ai) { return new DrinkAction(ai); }
        static Action* food(PlayerbotAI* ai) { return new EatAction(ai); }
        static Action* mana_potion(PlayerbotAI* ai) { return new UseManaPotion(ai); }
        static Action* healing_potion(PlayerbotAI* ai) { return new UseHealingPotion(ai); }
        static Action* healthstone(PlayerbotAI* ai) { return new UseItemAction(ai, "healthstone"); }
    };

};