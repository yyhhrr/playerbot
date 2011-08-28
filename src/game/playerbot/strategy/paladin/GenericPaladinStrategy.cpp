#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericPaladinStrategy.h"

using namespace ai;

class GenericPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericPaladinStrategyActionNodeFactory()
    {
        creators["seal of light"] = &seal_of_light;
        creators["cleanse"] = &cleanse;
        creators["cleanse poison on party"] = &cleanse_poison_on_party;
        creators["cleanse disease on party"] = &cleanse_disease_on_party;
        creators["seal of wisdom"] = &seal_of_wisdom;
        creators["seal of justice"] = &seal_of_justice;
        creators["hand of reckoning"] = &hand_of_reckoning;
        creators["judgement of wisdom"] = &judgement_of_wisdom;
        creators["divine shield"] = &divine_shield;
        creators["flash of light"] = &flash_of_light;
        creators["flash of light on party"] = &flash_of_light_on_party;
        creators["holy wrath"] = &holy_wrath;
        creators["lay on hands"] = &lay_on_hands;
    }
private:
    static ActionNode* lay_on_hands(PlayerbotAI* ai)
    {
        return new ActionNode ("lay on hands",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("divine shield"), new NextAction("flash of light"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* seal_of_light(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cleanse(PlayerbotAI* ai)
    {
        return new ActionNode ("cleanse",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cleanse_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("cleanse poison on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify poison on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cleanse_disease_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("cleanse disease on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("purify disease on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* seal_of_wisdom(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of justice"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* seal_of_justice(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of justice",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of righteousness"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* hand_of_reckoning(PlayerbotAI* ai)
    {
        return new ActionNode ("hand of reckoning",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of justice"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* judgement_of_wisdom(PlayerbotAI* ai)
    {
        return new ActionNode ("judgement of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of light"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* divine_shield(PlayerbotAI* ai)
    {
        return new ActionNode ("divine shield",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("divine protection"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* flash_of_light(PlayerbotAI* ai)
    {
        return new ActionNode ("flash of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* flash_of_light_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("flash of light on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* holy_wrath(PlayerbotAI* ai)
    {
        return new ActionNode ("holy wrath",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("consecration"), NULL),
            /*C*/ NULL);
    }
};

GenericPaladinStrategy::GenericPaladinStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericPaladinStrategyActionNodeFactory());
}

void GenericPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice snare",
        NextAction::array(0, new NextAction("hammer of justice", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("flash of light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("flash of light on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("divine protection", 51.0f), new NextAction("holy light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("divine protection on party", 40.0f), new NextAction("holy light on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"hammer of justice interrupt",
		NextAction::array(0, new NextAction("hammer of justice", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("lay on hands", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member critical health",
		NextAction::array(0, new NextAction("lay on hands on party", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"target critical health",
		NextAction::array(0, new NextAction("hammer of wrath", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse cure magic",
		NextAction::array(0, new NextAction("cleanse", 41.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse party member cure magic",
		NextAction::array(0, new NextAction("cleanse magic on party", 40.0f), NULL)));
}
