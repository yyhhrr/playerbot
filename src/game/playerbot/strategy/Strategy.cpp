#include "../../pchdef.h"
#include "../playerbot.h"
#include "Strategy.h"
#include "NamedObjectFactory.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
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

ActionNode* Strategy::createAction(const char* name)
{
    return actionFactoryInternal.create(name, ai);
}

void CombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new PanicTrigger(ai), 
        NextAction::array(0, new NextAction("healthstone", 100.0f), NULL)));

}

void MeleeCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("reach melee", 10.0f), NULL)));
}

void RangedCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        new EnemyOutOfSpellRangeTrigger(ai), 
        NextAction::array(0, new NextAction("reach spell", 10.0f), NULL)));
}
