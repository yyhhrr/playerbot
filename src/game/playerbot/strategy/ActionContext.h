#pragma once;

namespace ai
{
    class ActionContext : public NamedObjectContext<Action>
    {
    public:
        ActionContext()
        {
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
            creators["panic potion"] = &ActionContext::panic_potion;
            creators["healing potion"] = &ActionContext::healing_potion;
            creators["mana potion"] = &ActionContext::mana_potion;
            creators["eat"] = &ActionContext::eat;
            creators["drink"] = &ActionContext::drink;
            creators["tank assist"] = &ActionContext::tank_assist;
            creators["dps assist"] = &ActionContext::dps_assist;
            creators["loot"] = &ActionContext::loot;
            creators["loot all"] = &ActionContext::loot_all;
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
        static Action* shoot(AiManagerRegistry* ai) { return new CastShootAction(ai); }
        static Action* melee(AiManagerRegistry* ai) { return new MeleeAction(ai); }
        static Action* ReachSpell(AiManagerRegistry* ai) { return new ReachSpellAction(ai); }
        static Action* ReachMelee(AiManagerRegistry* ai) { return new ReachMeleeAction(ai); }
        static Action* flee(AiManagerRegistry* ai) { return new FleeAction(ai); }
        static Action* gift_of_the_naaru(AiManagerRegistry* ai) { return new CastGiftOfTheNaaruAction(ai); }
        static Action* lifeblood(AiManagerRegistry* ai) { return new CastLifeBloodAction(ai); }
        static Action* arcane_torrent(AiManagerRegistry* ai) { return new CastArcaneTorrentAction(ai); }
        static Action* end_pull(AiManagerRegistry* ai) { return new ChangeCombatStrategyAction(ai, "-pull"); }

        static Action* emote(AiManagerRegistry* ai) { return new EmoteAction(ai, 0); }
        static Action* attack_anything(AiManagerRegistry* ai) { return new AttackAnythingAction(ai); }
        static Action* stay_combat(AiManagerRegistry* ai) { return new StayCombatAction(ai); }
        static Action* stay_line(AiManagerRegistry* ai) { return new StayLineAction(ai); }
        static Action* stay_circle(AiManagerRegistry* ai) { return new StayCircleAction(ai); }
        static Action* stay(AiManagerRegistry* ai) { return new StayAction(ai); }
        static Action* goaway(AiManagerRegistry* ai) { return new GoAwayAction(ai); }
        static Action* follow_master(AiManagerRegistry* ai) { return new FollowMasterAction(ai); }
        static Action* follow_line(AiManagerRegistry* ai) { return new FollowLineAction(ai); }
        static Action* loot_all(AiManagerRegistry* ai) { return new LootAllAction(ai); }
        static Action* loot(AiManagerRegistry* ai) { return new LootAction(ai); }
        static Action* dps_assist(AiManagerRegistry* ai) { return new DpsAssistAction(ai); }
        static Action* tank_assist(AiManagerRegistry* ai) { return new TankAssistAction(ai); }
        static Action* drink(AiManagerRegistry* ai) { return new DrinkAction(ai); }
        static Action* eat(AiManagerRegistry* ai) { return new EatAction(ai); }
        static Action* mana_potion(AiManagerRegistry* ai) { return new UseManaPotion(ai); }
        static Action* healing_potion(AiManagerRegistry* ai) { return new UseHealingPotion(ai); }
        static Action* panic_potion(AiManagerRegistry* ai) { return new UsePanicPotion(ai); }
        static Action* healthstone(AiManagerRegistry* ai) { return new UseItemAction(ai, "healthstone"); }
    };

};