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
        creators["lose aggro"] = &TriggerFactoryInternal::LoseAggro;
    
        creators["light aoe"] = &TriggerFactoryInternal::LightAoe;
        creators["medium aoe"] = &TriggerFactoryInternal::MediumAoe;
        creators["high aoe"] = &TriggerFactoryInternal::HighAoe;
    }

private:
    Trigger* LightAoe(AiManagerRegistry* ai)
    {
        return new LightAoeTrigger(ai);
    }
    Trigger* MediumAoe(AiManagerRegistry* ai)
    {
        return new MediumAoeTrigger(ai);
    }
    Trigger* HighAoe(AiManagerRegistry* ai)
    {
        return new HighAoeTrigger(ai);
    }
    Trigger* LoseAggro(AiManagerRegistry* ai)
    {
        return new LoseAggroTrigger(ai);
    }
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


class ActionFactoryInternal : public NamedObjectFactory<Action, ActionFactoryInternal>
{
public:
    ActionFactoryInternal()
    {
        creators["melee"] = &ActionFactoryInternal::melee;
    }

private:
    Action* melee(AiManagerRegistry* ai)
    {
        return new MeleeAction(ai);
    }
    
};

static ActionFactoryInternal actionFactoryInternal;

Action* ActionFactory::createAction(const char* name)
{
    return actionFactoryInternal.create(name, ai);
}