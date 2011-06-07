#include "../../pchdef.h"
#include "../playerbot.h"
#include "ActionFactory.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "GenericNonCombatStrategy.h"
#include "RacialsStrategy.h"
#include "NamedObjectFactory.h"
#include "HealthTriggers.h"
#include "GenericTriggers.h"

using namespace ai;

class ActionFactoryInternal : public NamedObjectFactory<ActionNode, ActionFactoryInternal>
{
public:
    ActionFactoryInternal()
    {
        creators["flee"] = &ActionFactoryInternal::flee;
        creators["melee"] = &ActionFactoryInternal::melee;
        creators["reach melee"] = &ActionFactoryInternal::reach_melee;
        creators["reach spell"] = &ActionFactoryInternal::reach_spell;
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
    ActionNode* flee(AiManagerRegistry* ai)
    {
        return new ActionNode (new FleeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* melee(AiManagerRegistry* ai)
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* reach_melee(AiManagerRegistry* ai)
    {
        return new ActionNode (new ReachMeleeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* reach_spell(AiManagerRegistry* ai)
    {
        return new ActionNode (new ReachSpellAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* healthstone(AiManagerRegistry* ai)
    {
        return new ActionNode (new UseItemAction(ai, "healthstone"),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("panic potion"), NULL), 
            /*C*/ NULL);
    }
    ActionNode* panic_potion(AiManagerRegistry* ai)
    {
        return new ActionNode (new UsePanicPotion(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL), 
            /*C*/ NULL);
    }
    ActionNode* healing_potion(AiManagerRegistry* ai)
    {
        return new ActionNode (new UseHealingPotion(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL), 
            /*C*/ NULL);
    }
    ActionNode* mana_potion(AiManagerRegistry* ai)
    {
        return new ActionNode (new UseManaPotion(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL), 
            /*C*/ NULL);
    }
    ActionNode* eat(AiManagerRegistry* ai)
    {
        return new ActionNode (new EatAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* drink(AiManagerRegistry* ai)
    {
        return new ActionNode (new DrinkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* tank_assist(AiManagerRegistry* ai)
    {
        return new ActionNode (new TankAssistAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* dps_assist(AiManagerRegistry* ai)
    {
        return new ActionNode (new DpsAssistAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* loot(AiManagerRegistry* ai)
    {
        return new ActionNode (new LootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* loot_all(AiManagerRegistry* ai)
    {
        return new ActionNode (new LootAllAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* shoot(AiManagerRegistry* ai)
    {
        return new ActionNode (new CastShootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* follow_line(AiManagerRegistry* ai)
    {
        return new ActionNode (new FollowLineAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* follow_master(AiManagerRegistry* ai)
    {
        return new ActionNode (new FollowMasterAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* goaway(AiManagerRegistry* ai)
    {
        return new ActionNode (new GoAwayAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* stay(AiManagerRegistry* ai)
    {
        return new ActionNode (new StayAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* stay_circle(AiManagerRegistry* ai)
    {
        return new ActionNode (new StayCircleAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* stay_line(AiManagerRegistry* ai)
    {
        return new ActionNode (new StayLineAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* stay_combat(AiManagerRegistry* ai)
    {
        return new ActionNode (new StayCombatAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    ActionNode* attack_anything(AiManagerRegistry* ai)
    {
        return new ActionNode (new AttackAnythingAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("follow"), NULL), 
            /*C*/ NULL);
    }
    ActionNode* emote(AiManagerRegistry* ai)
    {
        return new ActionNode (new EmoteAction(ai, 0),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
};

static ActionFactoryInternal actionFactoryInternal;

ActionNode* ActionFactory::createAction(const char* name)
{
    return actionFactoryInternal.create(name, ai);
}

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
    Strategy* racials(AiManagerRegistry* ai)
    {
        return new RacialsStrategy(ai);
    }

    Strategy* follow_master(AiManagerRegistry* ai)
    {
        return new FollowMasterNonCombatStrategy(ai);
    }

    Strategy* follow_line(AiManagerRegistry* ai)
    {
        return new FollowLineNonCombatStrategy(ai);
    }

    Strategy* stay(AiManagerRegistry* ai)
    {
        return new StayNonCombatStrategy(ai);
    }

    Strategy* dps_assist(AiManagerRegistry* ai)
    {
        return new DpsAssistStrategy(ai);
    }

    Strategy* dps_aoe(AiManagerRegistry* ai)
    {
        return new DpsAoeStrategy(ai);
    }

    Strategy* tank_assist(AiManagerRegistry* ai)
    {
        return new TankAssistStrategy(ai);
    }

    Strategy* tank_aoe(AiManagerRegistry* ai)
    {
        return new TankAoeStrategy(ai);
    }

    Strategy* grind(AiManagerRegistry* ai)
    {
        return new GrindingStrategy(ai);
    }

    Strategy* loot(AiManagerRegistry* ai)
    {
        return new LootNonCombatStrategy(ai);
    }

    Strategy* goaway(AiManagerRegistry* ai)
    {
        return new GoAwayNonCombatStrategy(ai);
    }

    Strategy* emote(AiManagerRegistry* ai)
    {
        return new RandomEmoteStrategy(ai);
    }

    Strategy* passive(AiManagerRegistry* ai)
    {
        return new PassiveStrategy(ai);
    }

    Strategy* low_mana(AiManagerRegistry* ai)
    {
        return new LowManaStrategy(ai);
    }

    Strategy* food(AiManagerRegistry* ai)
    {
        return new UseFoodStrategy(ai);
    }
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

        creators["low health"] = &TriggerFactoryInternal::LowHealth;
        creators["low mana"] = &TriggerFactoryInternal::LowMana;
        
        creators["light rage available"] = &TriggerFactoryInternal::LightRageAvailable;
        creators["medium rage available"] = &TriggerFactoryInternal::MediumRageAvailable;
        creators["high rage available"] = &TriggerFactoryInternal::HighRageAvailable;
        
        creators["loot available"] = &TriggerFactoryInternal::LootAvailable;
        creators["no attackers"] = &TriggerFactoryInternal::NoAttackers;
        creators["no target"] = &TriggerFactoryInternal::NoTarget;
        
        creators["tank aoe"] = &TriggerFactoryInternal::TankAoe;
    }

private:
    Trigger* LowHealth(AiManagerRegistry* ai)
    {
        return new LowHealthTrigger(ai);
    }
    Trigger* LowMana(AiManagerRegistry* ai)
    {
        return new LowManaTrigger(ai);
    }
    Trigger* LightRageAvailable(AiManagerRegistry* ai)
    {
        return new LightRageAvailableTrigger(ai);
    }
    Trigger* MediumRageAvailable(AiManagerRegistry* ai)
    {
        return new MediumRageAvailableTrigger(ai);
    }
    Trigger* HighRageAvailable(AiManagerRegistry* ai)
    {
        return new HighRageAvailableTrigger(ai);
    }
    Trigger* LootAvailable(AiManagerRegistry* ai)
    {
        return new LootAvailableTrigger(ai);
    }
    Trigger* NoAttackers(AiManagerRegistry* ai)
    {
        return new NoAttackersTrigger(ai);
    }
    Trigger* TankAoe(AiManagerRegistry* ai)
    {
        return new TankAoeTrigger(ai);
    }
    Trigger* Timer(AiManagerRegistry* ai)
    {
        return new TimerTrigger(ai);
    }
    Trigger* NoTarget(AiManagerRegistry* ai)
    {
        return new NoTargetTrigger(ai);
    }
    Trigger* Random(AiManagerRegistry* ai)
    {
        return new RandomTrigger(ai);
    }

};

static TriggerFactoryInternal triggerFactoryInternal;

Trigger* ActionFactory::createTrigger(const char* name)
{
    return triggerFactoryInternal.create(name, ai);
}