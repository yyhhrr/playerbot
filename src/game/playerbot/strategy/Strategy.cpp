#include "../../pchdef.h"
#include "../playerbot.h"
#include "Strategy.h"
#include "NamedObjectFactory.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "GenericTriggers.h"

using namespace ai;


class ActionNodeFactoryInternal : public NamedObjectFactory<ActionNode, ActionNodeFactoryInternal>
{
public:
    ActionNodeFactoryInternal()
    {
        creators["flee"] = &ActionNodeFactoryInternal::flee;
        creators["melee"] = &ActionNodeFactoryInternal::melee;
        creators["reach melee"] = &ActionNodeFactoryInternal::reach_melee;
        creators["reach spell"] = &ActionNodeFactoryInternal::reach_spell;
        creators["healthstone"] = &ActionNodeFactoryInternal::healthstone;
        creators["panic potion"] = &ActionNodeFactoryInternal::panic_potion;
        creators["healing potion"] = &ActionNodeFactoryInternal::healing_potion;
        creators["mana potion"] = &ActionNodeFactoryInternal::mana_potion;
        creators["eat"] = &ActionNodeFactoryInternal::eat;
        creators["drink"] = &ActionNodeFactoryInternal::drink;
        creators["tank assist"] = &ActionNodeFactoryInternal::tank_assist;
        creators["dps assist"] = &ActionNodeFactoryInternal::dps_assist;
        creators["loot"] = &ActionNodeFactoryInternal::loot;
        creators["loot all"] = &ActionNodeFactoryInternal::loot_all;
        creators["shoot"] = &ActionNodeFactoryInternal::shoot;
        creators["follow line"] = &ActionNodeFactoryInternal::follow_line;
        creators["follow"] = &ActionNodeFactoryInternal::follow_master;
        creators["follow master"] = &ActionNodeFactoryInternal::follow_master;
        creators["goaway"] = &ActionNodeFactoryInternal::goaway;
        creators["stay"] = &ActionNodeFactoryInternal::stay;
        creators["stay circle"] = &ActionNodeFactoryInternal::stay_circle;
        creators["stay line"] = &ActionNodeFactoryInternal::stay_line;
        creators["stay combat"] = &ActionNodeFactoryInternal::stay_combat;
        creators["attack anything"] = &ActionNodeFactoryInternal::attack_anything;
        creators["emote"] = &ActionNodeFactoryInternal::emote;
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

static ActionNodeFactoryInternal ActionNodeFactoryInternal;

ActionNode* Strategy::createAction(const char* name)
{
    return ActionNodeFactoryInternal.create(name, ai);
}

void CombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        "panic", 
        NextAction::array(0, new NextAction("healthstone", 100.0f), NULL)));

}

void MeleeCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        "enemy out of melee", 
        NextAction::array(0, new NextAction("reach melee", 10.0f), NULL)));
}

void RangedCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        "enemy out of spell", 
        NextAction::array(0, new NextAction("reach spell", 10.0f), NULL)));
}
