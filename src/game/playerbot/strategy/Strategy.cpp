#include "../../pchdef.h"
#include "../playerbot.h"
#include "Strategy.h"
#include "NamedObjectContext.h"
#include "GenericActions.h"
#include "NonCombatActions.h"
#include "GenericTriggers.h"

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
    static ActionNode* flee(AiManagerRegistry* ai)
    {
        return new ActionNode ("flee",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* melee(AiManagerRegistry* ai)
    {
        return new ActionNode ("melee",  
            /*P*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* reach_melee(AiManagerRegistry* ai)
    {
        return new ActionNode ("reach melee",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* reach_spell(AiManagerRegistry* ai)
    {
        return new ActionNode ("reach spell",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* healthstone(AiManagerRegistry* ai)
    {
        return new ActionNode ("healthstone",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("panic potion"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* panic_potion(AiManagerRegistry* ai)
    {
        return new ActionNode ("panic potion",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* healing_potion(AiManagerRegistry* ai)
    {
        return new ActionNode ("healing potion",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* mana_potion(AiManagerRegistry* ai)
    {
        return new ActionNode ("mana potion",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* eat(AiManagerRegistry* ai)
    {
        return new ActionNode ("eat",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* drink(AiManagerRegistry* ai)
    {
        return new ActionNode ("drink",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* tank_assist(AiManagerRegistry* ai)
    {
        return new ActionNode ("tank assist",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* dps_assist(AiManagerRegistry* ai)
    {
        return new ActionNode ("dps assist",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* loot(AiManagerRegistry* ai)
    {
        return new ActionNode ("loot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* loot_all(AiManagerRegistry* ai)
    {
        return new ActionNode ("loot all",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* shoot(AiManagerRegistry* ai)
    {
        return new ActionNode ("shoot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* follow_line(AiManagerRegistry* ai)
    {
        return new ActionNode ("follow line",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* follow_master(AiManagerRegistry* ai)
    {
        return new ActionNode ("follow master",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* goaway(AiManagerRegistry* ai)
    {
        return new ActionNode ("goaway",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay(AiManagerRegistry* ai)
    {
        return new ActionNode ("stay",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay_circle(AiManagerRegistry* ai)
    {
        return new ActionNode ("stay circle",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay_line(AiManagerRegistry* ai)
    {
        return new ActionNode ("stay line",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* stay_combat(AiManagerRegistry* ai)
    {
        return new ActionNode ("stay combat",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    static ActionNode* attack_anything(AiManagerRegistry* ai)
    {
        return new ActionNode ("attack anything",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("follow"), NULL), 
            /*C*/ NULL);
    }
    static ActionNode* emote(AiManagerRegistry* ai)
    {
        return new ActionNode ("emote",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
};

static ActionNodeFactoryInternal ActionNodeFactoryInternal;

ActionNode* Strategy::GetAction(const char* name)
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
