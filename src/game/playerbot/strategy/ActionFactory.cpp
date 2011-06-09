#include "../../pchdef.h"
#include "../playerbot.h"
#include "ActionFactory.h"
#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"
#include "NamedObjectFactory.h"
#include "HealthTriggers.h"
#include "GenericTriggers.h"
#include "GenericActions.h"

using namespace ai;

class StrategyFactoryInternal : public NamedObjectFactory<Strategy, StrategyFactoryInternal>
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
    Strategy* racials(AiManagerRegistry* ai) { return new RacialsStrategy(ai); }
    Strategy* follow_master(AiManagerRegistry* ai) { return new FollowMasterNonCombatStrategy(ai); }
    Strategy* follow_line(AiManagerRegistry* ai) { return new FollowLineNonCombatStrategy(ai); }
    Strategy* stay(AiManagerRegistry* ai) { return new StayNonCombatStrategy(ai); }
    Strategy* dps_assist(AiManagerRegistry* ai) { return new DpsAssistStrategy(ai); }
    Strategy* dps_aoe(AiManagerRegistry* ai) { return new DpsAoeStrategy(ai); }
    Strategy* tank_assist(AiManagerRegistry* ai) { return new TankAssistStrategy(ai); }
    Strategy* tank_aoe(AiManagerRegistry* ai) { return new TankAoeStrategy(ai); }
    Strategy* grind(AiManagerRegistry* ai) { return new GrindingStrategy(ai); }
    Strategy* loot(AiManagerRegistry* ai) { return new LootNonCombatStrategy(ai); }
    Strategy* goaway(AiManagerRegistry* ai) { return new GoAwayNonCombatStrategy(ai); }
    Strategy* emote(AiManagerRegistry* ai) { return new RandomEmoteStrategy(ai); }
    Strategy* passive(AiManagerRegistry* ai) { return new PassiveStrategy(ai); }
    Strategy* low_mana(AiManagerRegistry* ai) { return new LowManaStrategy(ai); }
    Strategy* food(AiManagerRegistry* ai) { return new UseFoodStrategy(ai); }
};

static StrategyFactoryInternal strategyFactoryInternal;


Strategy* ActionFactory::createStrategy(const char* name)
{
    return strategyFactoryInternal.create(name, ai);
}


class TriggerFactoryInternal : public NamedObjectFactory<Trigger, TriggerFactoryInternal>
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
        creators["enemy too close"] = &TriggerFactoryInternal::EnemyTooClose;

        creators["combo points available"] = &TriggerFactoryInternal::ComboPointsAvailable;

        creators["medium threat"] = &TriggerFactoryInternal::MediumThreat;
        
        creators["party member dead"] = &TriggerFactoryInternal::PartyMemberDead;
        creators["no pet"] = &TriggerFactoryInternal::no_pet;
        creators["has attackers"] = &TriggerFactoryInternal::has_attackers;
    
        creators["no drink"] = &TriggerFactoryInternal::no_drink;
        creators["no food"] = &TriggerFactoryInternal::no_food;
        
        creators["behind target"] = &TriggerFactoryInternal::behind_target;
    }

private:
    Trigger* behind_target(AiManagerRegistry* ai) { return new IsBehindTargetTrigger(ai); }
    Trigger* no_drink(AiManagerRegistry* ai) { return new NoDrinkTrigger(ai); }
    Trigger* no_food(AiManagerRegistry* ai) { return new NoFoodTrigger(ai); }
    Trigger* LightAoe(AiManagerRegistry* ai) { return new LightAoeTrigger(ai); }
    Trigger* MediumAoe(AiManagerRegistry* ai) { return new MediumAoeTrigger(ai); }
    Trigger* HighAoe(AiManagerRegistry* ai) { return new HighAoeTrigger(ai); }
    Trigger* LoseAggro(AiManagerRegistry* ai) { return new LoseAggroTrigger(ai); }
    Trigger* LowHealth(AiManagerRegistry* ai) { return new LowHealthTrigger(ai); }
    Trigger* MediumHealth(AiManagerRegistry* ai) { return new MediumHealthTrigger(ai); }
    Trigger* CriticalHealth(AiManagerRegistry* ai) { return new CriticalHealthTrigger(ai); }
    Trigger* TargetCriticalHealth(AiManagerRegistry* ai) { return new TargetCriticalHealthTrigger(ai); }
    Trigger* LowMana(AiManagerRegistry* ai) { return new LowManaTrigger(ai); }
    Trigger* LightRageAvailable(AiManagerRegistry* ai) { return new LightRageAvailableTrigger(ai); }
    Trigger* MediumRageAvailable(AiManagerRegistry* ai) { return new MediumRageAvailableTrigger(ai); }
    Trigger* HighRageAvailable(AiManagerRegistry* ai) { return new HighRageAvailableTrigger(ai); }
    Trigger* LightEnergyAvailable(AiManagerRegistry* ai) { return new LightEnergyAvailableTrigger(ai); }
    Trigger* MediumEnergyAvailable(AiManagerRegistry* ai) { return new MediumEnergyAvailableTrigger(ai); }
    Trigger* HighEnergyAvailable(AiManagerRegistry* ai) { return new HighEnergyAvailableTrigger(ai); }
    Trigger* LootAvailable(AiManagerRegistry* ai) { return new LootAvailableTrigger(ai); }
    Trigger* NoAttackers(AiManagerRegistry* ai) { return new NoAttackersTrigger(ai); }
    Trigger* TankAoe(AiManagerRegistry* ai) { return new TankAoeTrigger(ai); }
    Trigger* Timer(AiManagerRegistry* ai) { return new TimerTrigger(ai); }
    Trigger* NoTarget(AiManagerRegistry* ai) { return new NoTargetTrigger(ai); }
    Trigger* Random(AiManagerRegistry* ai) { return new RandomTrigger(ai); }
    Trigger* EnemyOutOfMelee(AiManagerRegistry* ai) { return new EnemyOutOfMeleeTrigger(ai); }
    Trigger* EnemyTooClose(AiManagerRegistry* ai) { return new EnemyTooCloseTrigger(ai); }
    Trigger* ComboPointsAvailable(AiManagerRegistry* ai) { return new ComboPointsAvailableTrigger(ai); }
    Trigger* MediumThreat(AiManagerRegistry* ai) { return new MediumThreatTrigger(ai); }
    Trigger* PartyMemberDead(AiManagerRegistry* ai) { return new PartyMemberDeadTrigger(ai); }
    Trigger* PartyMemberLowHealth(AiManagerRegistry* ai) { return new PartyMemberLowHealthTrigger(ai); }
    Trigger* PartyMemberMediumHealth(AiManagerRegistry* ai) { return new PartyMemberMediumHealthTrigger(ai); }
    Trigger* PartyMemberCriticalHealth(AiManagerRegistry* ai) { return new PartyMemberCriticalHealthTrigger(ai); }
    Trigger* no_pet(AiManagerRegistry* ai) { return new NoPetTrigger(ai); }
    Trigger* has_attackers(AiManagerRegistry* ai) { return new HasAttackersTrigger(ai); }
    
};

static TriggerFactoryInternal triggerFactoryInternal;

Trigger* ActionFactory::createTrigger(const char* name)
{
    return triggerFactoryInternal.create(name, ai);
}


class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
{
public:
    ActionFactoryInternal()
    {
        creators["melee"] = &ActionFactoryInternal::melee;
        creators["reach spell"] = &ActionFactoryInternal::ReachSpell;
        creators["reach melee"] = &ActionFactoryInternal::ReachMelee;
        creators["flee"] = &ActionFactoryInternal::flee;
        creators["gift of the naaru"] = &ActionFactoryInternal::gift_of_the_naaru;
    }

private:
    Action* melee(AiManagerRegistry* ai) { return new MeleeAction(ai); }
    Action* ReachSpell(AiManagerRegistry* ai) { return new ReachSpellAction(ai); }
    Action* ReachMelee(AiManagerRegistry* ai) { return new ReachMeleeAction(ai); }
    Action* flee(AiManagerRegistry* ai) { return new FleeAction(ai); }
    Action* gift_of_the_naaru(AiManagerRegistry* ai) { return new CastGiftOfTheNaaruAction(ai); }
    

};

static ActionFactoryInternal actionFactoryInternal;

Action* ActionFactory::createAction(const char* name)
{
    return actionFactoryInternal.create(name, ai);
}
