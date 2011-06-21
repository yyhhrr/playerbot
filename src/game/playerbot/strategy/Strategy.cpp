#include "../../pchdef.h"
#include "../playerbot.h"
#include "Strategy.h"
#include "NamedObjectContext.h"

using namespace ai;


class ActionNodeFactoryInternal : public NamedObjectContextBase<ActionNode>
{
public:
    ActionNodeFactoryInternal()
    {
        creators["flee"] = &ActionNodeFactoryInternal::flee;
        creators["melee"] = &ActionNodeFactoryInternal::melee;
        creators["reach melee"] = &ActionNodeFactoryInternal::reach_melee;
        creators["reach spell"] = &ActionNodeFactoryInternal::reach_spell;
        creators["healthstone"] = &ActionNodeFactoryInternal::healthstone;
        creators["healing potion"] = &ActionNodeFactoryInternal::healing_potion;
        creators["mana potion"] = &ActionNodeFactoryInternal::mana_potion;
        creators["food"] = &ActionNodeFactoryInternal::food;
        creators["drink"] = &ActionNodeFactoryInternal::drink;
        creators["tank assist"] = &ActionNodeFactoryInternal::tank_assist;
        creators["dps assist"] = &ActionNodeFactoryInternal::dps_assist;
        creators["loot"] = &ActionNodeFactoryInternal::loot;
        creators["add all loot"] = &ActionNodeFactoryInternal::add_all_loot;
        creators["shoot"] = &ActionNodeFactoryInternal::shoot;
        creators["follow line"] = &ActionNodeFactoryInternal::follow_line;
        creators["follow"] = &ActionNodeFactoryInternal::follow_master;
        creators["follow master"] = &ActionNodeFactoryInternal::follow_master;
        creators["be near"] = &ActionNodeFactoryInternal::follow_master_random;
        creators["goaway"] = &ActionNodeFactoryInternal::goaway;
        creators["stay"] = &ActionNodeFactoryInternal::stay;
        creators["stay circle"] = &ActionNodeFactoryInternal::stay_circle;
        creators["stay line"] = &ActionNodeFactoryInternal::stay_line;
        creators["stay combat"] = &ActionNodeFactoryInternal::stay_combat;
        creators["attack anything"] = &ActionNodeFactoryInternal::attack_anything;
        creators["emote"] = &ActionNodeFactoryInternal::emote;
        creators["move random"] = &ActionNodeFactoryInternal::move_random;
    }

private:
    static ActionNode* flee(PlayerbotAI* ai)
    {
        return new ActionNode ("flee",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",  
            /*P*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* reach_melee(PlayerbotAI* ai)
    {
        return new ActionNode ("reach melee",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* reach_spell(PlayerbotAI* ai)
    {
        return new ActionNode ("reach spell",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* healthstone(PlayerbotAI* ai)
    {
        return new ActionNode ("healthstone",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* healing_potion(PlayerbotAI* ai)
    {
        return new ActionNode ("healing potion",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* mana_potion(PlayerbotAI* ai)
    {
        return new ActionNode ("mana potion",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* food(PlayerbotAI* ai)
    {
        return new ActionNode ("food",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* drink(PlayerbotAI* ai)
    {
        return new ActionNode ("drink",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* tank_assist(PlayerbotAI* ai)
    {
        return new ActionNode ("tank assist",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* dps_assist(PlayerbotAI* ai)
    {
        return new ActionNode ("dps assist",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* loot(PlayerbotAI* ai)
    {
        return new ActionNode ("loot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* add_all_loot(PlayerbotAI* ai)
    {
        return new ActionNode ("add all loot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* shoot(PlayerbotAI* ai)
    {
        return new ActionNode ("shoot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* follow_line(PlayerbotAI* ai)
    {
        return new ActionNode ("follow line",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* follow_master(PlayerbotAI* ai)
    {
        return new ActionNode ("follow master",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* follow_master_random(PlayerbotAI* ai)
    {
        return new ActionNode ("be near",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("follow master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* goaway(PlayerbotAI* ai)
    {
        return new ActionNode ("goaway",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay(PlayerbotAI* ai)
    {
        return new ActionNode ("stay",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay_circle(PlayerbotAI* ai)
    {
        return new ActionNode ("stay circle",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay_line(PlayerbotAI* ai)
    {
        return new ActionNode ("stay line",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay_combat(PlayerbotAI* ai)
    {
        return new ActionNode ("stay combat",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* attack_anything(PlayerbotAI* ai)
    {
        return new ActionNode ("attack anything",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("follow"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* emote(PlayerbotAI* ai)
    {
        return new ActionNode ("emote",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* move_random(PlayerbotAI* ai)
    {
        return new ActionNode ("move random",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("stay line"), NULL),
            /*C*/ NULL);
    }
};

static ActionNodeFactoryInternal ActionNodeFactoryInternal;

ActionNode* Strategy::GetAction(string name)
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
