#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"

using namespace ai;

class GenericShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericShamanStrategyActionNodeFactory()
    {
        creators["flametongue weapon"] = &flametongue_weapon;
        creators["frostbrand weapon"] = &frostbrand_weapon;
        creators["windfury weapon"] = &windfury_weapon;
        creators["lesser healing wave"] = &lesser_healing_wave;
        creators["lesser healing wave on party"] = &lesser_healing_wave_on_party;
        creators["chain heal"] = &chain_heal;
        creators["riptide"] = &riptide;
        creators["chain heal on party"] = &chain_heal_on_party;
        creators["riptide on party"] = &riptide_on_party;
    }
private:
    static ActionNode* flametongue_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("flametongue weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbrand weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frostbrand_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("frostbrand weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* windfury_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("windfury weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lesser_healing_wave(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser healing wave",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lesser_healing_wave_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser healing wave on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* chain_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("chain heal",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser healing wave"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* riptide(PlayerbotAI* ai)
    {
        return new ActionNode ("riptide",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* chain_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("chain heal on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser healing wave on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* riptide_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("riptide on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
            /*C*/ NULL);
    }
};

GenericShamanStrategy::GenericShamanStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericShamanStrategyActionNodeFactory());
}

void GenericShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "windfury totem",
        NextAction::array(0, new NextAction("windfury totem", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mana spring totem",
        NextAction::array(0, new NextAction("mana spring totem", 16.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "strength of earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear",
        NextAction::array(0, new NextAction("wind shear", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "purge",
		NextAction::array(0, new NextAction("purge", 10.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0, new NextAction("chain heal on party", 25.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0, new NextAction("riptide on party", 25.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium health",
		NextAction::array(0, new NextAction("chain heal", 26.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"low health",
		NextAction::array(0, new NextAction("riptide", 26.0f), NULL)));
}
