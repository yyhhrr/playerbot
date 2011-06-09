#include "../../pchdef.h"
#include "../playerbot.h"
#include "ActionFactory.h"
#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"
#include "NamedObjectFactory.h"
#include "HealthTriggers.h"
#include "GenericTriggers.h"
#include "GenericActions.h"
#include "NonCombatActions.h"

using namespace ai;


class StrategyFactoryInternal : public NamedObjectFactory<Strategy>
{
public:
    StrategyFactoryInternal()
    {
        creators["racials"] = &StrategyFactoryInternal::racials;
        creators["follow master"] = &StrategyFactoryInternal::follow_master;
        creators["follow line"] = &StrategyFactoryInternal::follow_line;
        creators["stay"] = &StrategyFactoryInternal::stay;
        creators["dps assist"] = &StrategyFactoryInternal::dps_assist;
        creators["dps aoe"] = &StrategyFactoryInternal::dps_aoe;
        creators["tank assist"] = &StrategyFactoryInternal::tank_assist;
        creators["tank aoe"] = &StrategyFactoryInternal::tank_aoe;
        creators["grind"] = &StrategyFactoryInternal::grind;
        creators["loot"] = &StrategyFactoryInternal::loot;
        creators["goaway"] = &StrategyFactoryInternal::goaway;
        creators["emote"] = &StrategyFactoryInternal::emote;
        creators["passive"] = &StrategyFactoryInternal::passive;
        creators["low mana"] = &StrategyFactoryInternal::low_mana;
        creators["food"] = &StrategyFactoryInternal::food;
    }

private:
    static Strategy* racials(AiManagerRegistry* ai) { return new RacialsStrategy(ai); }
    static Strategy* follow_master(AiManagerRegistry* ai) { return new FollowMasterNonCombatStrategy(ai); }
    static Strategy* follow_line(AiManagerRegistry* ai) { return new FollowLineNonCombatStrategy(ai); }
    static Strategy* stay(AiManagerRegistry* ai) { return new StayNonCombatStrategy(ai); }
    static Strategy* dps_assist(AiManagerRegistry* ai) { return new DpsAssistStrategy(ai); }
    static Strategy* dps_aoe(AiManagerRegistry* ai) { return new DpsAoeStrategy(ai); }
    static Strategy* tank_assist(AiManagerRegistry* ai) { return new TankAssistStrategy(ai); }
    static Strategy* tank_aoe(AiManagerRegistry* ai) { return new TankAoeStrategy(ai); }
    static Strategy* grind(AiManagerRegistry* ai) { return new GrindingStrategy(ai); }
    static Strategy* loot(AiManagerRegistry* ai) { return new LootNonCombatStrategy(ai); }
    static Strategy* goaway(AiManagerRegistry* ai) { return new GoAwayNonCombatStrategy(ai); }
    static Strategy* emote(AiManagerRegistry* ai) { return new RandomEmoteStrategy(ai); }
    static Strategy* passive(AiManagerRegistry* ai) { return new PassiveStrategy(ai); }
    static Strategy* low_mana(AiManagerRegistry* ai) { return new LowManaStrategy(ai); }
    static Strategy* food(AiManagerRegistry* ai) { return new UseFoodStrategy(ai); }
};

class TriggerFactoryInternal : public NamedObjectFactory<Trigger>
{
public:
    TriggerFactoryInternal()
    {
        creators["timer"] = &TriggerFactoryInternal::Timer;
        creators["random"] = &TriggerFactoryInternal::Random;

        creators["target critical health"] = &TriggerFactoryInternal::TargetCriticalHealth;
        creators["critical health"] = &TriggerFactoryInternal::CriticalHealth;
        creators["low health"] = &TriggerFactoryInternal::LowHealth;
        creators["medium health"] = &TriggerFactoryInternal::MediumHealth;
        creators["low mana"] = &TriggerFactoryInternal::LowMana;

        creators["party member critical health"] = &TriggerFactoryInternal::PartyMemberCriticalHealth;
        creators["party member low health"] = &TriggerFactoryInternal::PartyMemberLowHealth;
        creators["party member medium health"] = &TriggerFactoryInternal::PartyMemberMediumHealth;

        creators["light rage available"] = &TriggerFactoryInternal::LightRageAvailable;
        creators["medium rage available"] = &TriggerFactoryInternal::MediumRageAvailable;
        creators["high rage available"] = &TriggerFactoryInternal::HighRageAvailable;

        creators["light energy available"] = &TriggerFactoryInternal::LightEnergyAvailable;
        creators["medium energy available"] = &TriggerFactoryInternal::MediumEnergyAvailable;
        creators["high energy available"] = &TriggerFactoryInternal::HighEnergyAvailable;

        creators["loot available"] = &TriggerFactoryInternal::LootAvailable;
        creators["no attackers"] = &TriggerFactoryInternal::NoAttackers;
        creators["no target"] = &TriggerFactoryInternal::NoTarget;

        creators["tank aoe"] = &TriggerFactoryInternal::TankAoe;
        creators["lose aggro"] = &TriggerFactoryInternal::LoseAggro;

        creators["light aoe"] = &TriggerFactoryInternal::LightAoe;
        creators["medium aoe"] = &TriggerFactoryInternal::MediumAoe;
        creators["high aoe"] = &TriggerFactoryInternal::HighAoe;

        creators["enemy out of melee"] = &TriggerFactoryInternal::EnemyOutOfMelee;
        creators["enemy out of spell"] = &TriggerFactoryInternal::EnemyOutOfSpell;
        creators["enemy too close"] = &TriggerFactoryInternal::EnemyTooClose;

        creators["combo points available"] = &TriggerFactoryInternal::ComboPointsAvailable;

        creators["medium threat"] = &TriggerFactoryInternal::MediumThreat;
        
        creators["party member dead"] = &TriggerFactoryInternal::PartyMemberDead;
        creators["no pet"] = &TriggerFactoryInternal::no_pet;
        creators["has attackers"] = &TriggerFactoryInternal::has_attackers;
    
        creators["no drink"] = &TriggerFactoryInternal::no_drink;
        creators["no food"] = &TriggerFactoryInternal::no_food;
        
        creators["panic"] = &TriggerFactoryInternal::panic;
        creators["behind target"] = &TriggerFactoryInternal::behind_target;
    }

private:
    static Trigger* behind_target(AiManagerRegistry* ai) { return new IsBehindTargetTrigger(ai); }
    static Trigger* panic(AiManagerRegistry* ai) { return new PanicTrigger(ai); }
    static Trigger* no_drink(AiManagerRegistry* ai) { return new NoDrinkTrigger(ai); }
    static Trigger* no_food(AiManagerRegistry* ai) { return new NoFoodTrigger(ai); }
    static Trigger* LightAoe(AiManagerRegistry* ai) { return new LightAoeTrigger(ai); }
    static Trigger* MediumAoe(AiManagerRegistry* ai) { return new MediumAoeTrigger(ai); }
    static Trigger* HighAoe(AiManagerRegistry* ai) { return new HighAoeTrigger(ai); }
    static Trigger* LoseAggro(AiManagerRegistry* ai) { return new LoseAggroTrigger(ai); }
    static Trigger* LowHealth(AiManagerRegistry* ai) { return new LowHealthTrigger(ai); }
    static Trigger* MediumHealth(AiManagerRegistry* ai) { return new MediumHealthTrigger(ai); }
    static Trigger* CriticalHealth(AiManagerRegistry* ai) { return new CriticalHealthTrigger(ai); }
    static Trigger* TargetCriticalHealth(AiManagerRegistry* ai) { return new TargetCriticalHealthTrigger(ai); }
    static Trigger* LowMana(AiManagerRegistry* ai) { return new LowManaTrigger(ai); }
    static Trigger* LightRageAvailable(AiManagerRegistry* ai) { return new LightRageAvailableTrigger(ai); }
    static Trigger* MediumRageAvailable(AiManagerRegistry* ai) { return new MediumRageAvailableTrigger(ai); }
    static Trigger* HighRageAvailable(AiManagerRegistry* ai) { return new HighRageAvailableTrigger(ai); }
    static Trigger* LightEnergyAvailable(AiManagerRegistry* ai) { return new LightEnergyAvailableTrigger(ai); }
    static Trigger* MediumEnergyAvailable(AiManagerRegistry* ai) { return new MediumEnergyAvailableTrigger(ai); }
    static Trigger* HighEnergyAvailable(AiManagerRegistry* ai) { return new HighEnergyAvailableTrigger(ai); }
    static Trigger* LootAvailable(AiManagerRegistry* ai) { return new LootAvailableTrigger(ai); }
    static Trigger* NoAttackers(AiManagerRegistry* ai) { return new NoAttackersTrigger(ai); }
    static Trigger* TankAoe(AiManagerRegistry* ai) { return new TankAoeTrigger(ai); }
    static Trigger* Timer(AiManagerRegistry* ai) { return new TimerTrigger(ai); }
    static Trigger* NoTarget(AiManagerRegistry* ai) { return new NoTargetTrigger(ai); }
    static Trigger* Random(AiManagerRegistry* ai) { return new RandomTrigger(ai); }
    static Trigger* EnemyOutOfMelee(AiManagerRegistry* ai) { return new EnemyOutOfMeleeTrigger(ai); }
    static Trigger* EnemyOutOfSpell(AiManagerRegistry* ai) { return new EnemyOutOfSpellRangeTrigger(ai); }
    static Trigger* EnemyTooClose(AiManagerRegistry* ai) { return new EnemyTooCloseTrigger(ai); }
    static Trigger* ComboPointsAvailable(AiManagerRegistry* ai) { return new ComboPointsAvailableTrigger(ai); }
    static Trigger* MediumThreat(AiManagerRegistry* ai) { return new MediumThreatTrigger(ai); }
    static Trigger* PartyMemberDead(AiManagerRegistry* ai) { return new PartyMemberDeadTrigger(ai); }
    static Trigger* PartyMemberLowHealth(AiManagerRegistry* ai) { return new PartyMemberLowHealthTrigger(ai); }
    static Trigger* PartyMemberMediumHealth(AiManagerRegistry* ai) { return new PartyMemberMediumHealthTrigger(ai); }
    static Trigger* PartyMemberCriticalHealth(AiManagerRegistry* ai) { return new PartyMemberCriticalHealthTrigger(ai); }
    static Trigger* no_pet(AiManagerRegistry* ai) { return new NoPetTrigger(ai); }
    static Trigger* has_attackers(AiManagerRegistry* ai) { return new HasAttackersTrigger(ai); }
    
};

class ActionFactoryInternal : public NamedObjectFactory<Action>
{
public:
    ActionFactoryInternal()
    {
        creators["melee"] = &ActionFactoryInternal::melee;
        creators["reach spell"] = &ActionFactoryInternal::ReachSpell;
        creators["reach melee"] = &ActionFactoryInternal::ReachMelee;
        creators["flee"] = &ActionFactoryInternal::flee;
        creators["gift of the naaru"] = &ActionFactoryInternal::gift_of_the_naaru;
        creators["shoot"] = &ActionFactoryInternal::shoot;
        creators["lifeblood"] = &ActionFactoryInternal::lifeblood;
        creators["arcane torrent"] = &ActionFactoryInternal::arcane_torrent;
        creators["end pull"] = &ActionFactoryInternal::end_pull;
        creators["healthstone"] = &ActionFactoryInternal::healthstone;
        creators["panic potion"] = &ActionFactoryInternal::panic_potion;
        creators["healing potion"] = &ActionFactoryInternal::healing_potion;
        creators["mana potion"] = &ActionFactoryInternal::mana_potion;
        creators["eat"] = &ActionFactoryInternal::eat;
        creators["drink"] = &ActionFactoryInternal::drink;
        creators["tank assist"] = &ActionFactoryInternal::tank_assist;
        creators["dps assist"] = &ActionFactoryInternal::dps_assist;
        creators["loot"] = &ActionFactoryInternal::loot;
        creators["loot all"] = &ActionFactoryInternal::loot_all;
        creators["shoot"] = &ActionFactoryInternal::shoot;
        creators["follow line"] = &ActionFactoryInternal::follow_line;
        creators["follow"] = &ActionFactoryInternal::follow_master;
        creators["follow master"] = &ActionFactoryInternal::follow_master;
        creators["goaway"] = &ActionFactoryInternal::goaway;
        creators["stay"] = &ActionFactoryInternal::stay;
        creators["stay circle"] = &ActionFactoryInternal::stay_circle;
        creators["stay line"] = &ActionFactoryInternal::stay_line;
        creators["stay combat"] = &ActionFactoryInternal::stay_combat;
        creators["attack anything"] = &ActionFactoryInternal::attack_anything;
        creators["emote"] = &ActionFactoryInternal::emote;
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

Action* ActionFactory::createAction(const char* name)
{
    for (list<NamedObjectFactory<Action>*>::iterator i = actionFactories.begin(); i != actionFactories.end(); i++)
    {
        Action* action = (*i)->create(name, ai);
        if (action) return action;
    }
    return NULL;
}

Trigger* ActionFactory::createTrigger(const char* name)
{
    for (list<NamedObjectFactory<Trigger>*>::iterator i = triggerFactories.begin(); i != triggerFactories.end(); i++)
    {
        Trigger* trigger = (*i)->create(name, ai);
        if (trigger) return trigger;
    }
    return NULL;
}

Strategy* ActionFactory::createStrategy(const char* name)
{
    for (list<NamedObjectFactory<Strategy>*>::iterator i = strategyFactories.begin(); i != strategyFactories.end(); i++)
    {
        Strategy* strategy = (*i)->create(name, ai);
        if (strategy) return strategy;
    }
    return NULL;
}

ActionFactory::ActionFactory(AiManagerRegistry* const ai) : AiManagerRegistryAware(ai) 
{
    strategyFactories.push_back(new StrategyFactoryInternal());
    actionFactories.push_back(new ActionFactoryInternal());
    triggerFactories.push_back(new TriggerFactoryInternal());
}

ActionFactory::~ActionFactory() 
{
    for (list<NamedObjectFactory<Strategy>*>::iterator i = strategyFactories.begin(); i != strategyFactories.end(); i++)
        delete *i;

    for (list<NamedObjectFactory<Action>*>::iterator i = actionFactories.begin(); i != actionFactories.end(); i++)
        delete *i;

    for (list<NamedObjectFactory<Trigger>*>::iterator i = triggerFactories.begin(); i != triggerFactories.end(); i++)
        delete *i;
}

