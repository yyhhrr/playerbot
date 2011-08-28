#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"

using namespace ai;

class GenericPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericPriestStrategyActionNodeFactory()
    {
        creators["inner fire"] = &inner_fire;
        creators["holy nova"] = &holy_nova;
        creators["power word: fortitude"] = &power_word_fortitude;
        creators["power word: fortitude on party"] = &power_word_fortitude_on_party;
        creators["divine spirit"] = &divine_spirit;
        creators["divine spirit on party"] = &divine_spirit_on_party;
        creators["power word: shield"] = &power_word_shield;
        creators["power word: shield on party"] = &power_word_shield_on_party;
        creators["renew"] = &renew;
        creators["renew on party"] = &renew_on_party;
        creators["greater heal"] = &greater_heal;
        creators["greater heal on party"] = &greater_heal_on_party;
        creators["heal"] = &heal;
        creators["heal on party"] = &heal_on_party;
        creators["lesser heal"] = &lesser_heal;
        creators["lesser heal on party"] = &lesser_heal_on_party;
        creators["flash heal"] = &flash_heal;
        creators["flash heal on party"] = &flash_heal_on_party;
    }
private:
    static ActionNode* inner_fire(PlayerbotAI* ai)
    {
        return new ActionNode ("inner fire",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* holy_nova(PlayerbotAI* ai)
    {
        return new ActionNode ("holy nova",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* power_word_fortitude(PlayerbotAI* ai)
    {
        return new ActionNode ("power word: fortitude",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* power_word_fortitude_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("power word: fortitude on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* divine_spirit(PlayerbotAI* ai)
    {
        return new ActionNode ("divine spirit",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* divine_spirit_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("divine spirit on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* power_word_shield(PlayerbotAI* ai)
    {
        return new ActionNode ("power word: shield",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), NULL),
            /*C*/ NULL);
    }
    static ActionNode* power_word_shield_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("power word: shield on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), NULL),
            /*C*/ NULL);
    }
    static ActionNode* renew(PlayerbotAI* ai)
    {
        return new ActionNode ("renew",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* renew_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("renew on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* greater_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("greater heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* greater_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("greater heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* heal(PlayerbotAI* ai)
    {
        return new ActionNode ("heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lesser_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* lesser_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* flash_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("flash heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("greater heal"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* flash_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("flash heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("greater heal on party"), NULL),
            /*C*/ NULL);
    }
};

GenericPriestStrategy::GenericPriestStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericPriestStrategyActionNodeFactory());
}

void GenericPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash heal", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash heal on party", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("power word: shield", 70.0f), new NextAction("flash heal", 70.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", 60.0f), new NextAction("flash heal on party", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("power word: shield", 60.0f), new NextAction("greater heal", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", 50.0f), new NextAction("greater heal on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", 31.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close",
        NextAction::array(0, new NextAction("fade", 50.0f), new NextAction("flee", 49.0f), NULL)));

}
