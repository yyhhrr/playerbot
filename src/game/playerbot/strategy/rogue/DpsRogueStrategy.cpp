#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueMultipliers.h"
#include "DpsRogueStrategy.h"

using namespace ai;

class DpsRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsRogueStrategyActionNodeFactory()
    {
        creators["mutilate"] = &mutilate;
        creators["kidney shot"] = &kidney_shot;
        creators["rupture"] = &rupture;
        creators["slice and dice"] = &slice_and_dice;
        creators["backstab"] = &backstab;
    }
private:
    static ActionNode* mutilate(PlayerbotAI* ai)
    {
        return new ActionNode ("mutilate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sinister strike"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* kidney_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("kidney shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rupture"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rupture(PlayerbotAI* ai)
    {
        return new ActionNode ("rupture",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("slice and dice"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* slice_and_dice(PlayerbotAI* ai)
    {
        return new ActionNode ("slice and dice",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("eviscerate"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* backstab(PlayerbotAI* ai)
    {
        return new ActionNode ("backstab",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mutilate"), NULL),
            /*C*/ NULL);
    }
};

DpsRogueStrategy::DpsRogueStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new DpsRogueStrategyActionNodeFactory());
}

NextAction** DpsRogueStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void DpsRogueStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("melee", 10.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"high energy available",
		NextAction::array(0, new NextAction("mutilate", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "combo points available",
        NextAction::array(0, new NextAction("kidney shot", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium threat",
		NextAction::array(0, new NextAction("vanish", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"low health",
		NextAction::array(0, new NextAction("evasion", 50.0f), new NextAction("feint", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"kick",
		NextAction::array(0, new NextAction("kick", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("backstab", 21.0f), NULL)));
}
