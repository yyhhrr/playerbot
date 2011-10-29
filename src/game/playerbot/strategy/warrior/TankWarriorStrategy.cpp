#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "TankWarriorStrategy.h"

using namespace ai;

class TankWarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    TankWarriorStrategyActionNodeFactory()
    {
        creators["melee"] = &melee;
        creators["shield wall"] = &shield_wall;
        creators["rend"] = &rend;
        creators["revenge"] = &revenge;
        creators["devastate"] = &devastate;
        creators["shockwave"] = &shockwave;
    }
private:
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), new NextAction("reach melee"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* shield_wall(PlayerbotAI* ai)
    {
        return new ActionNode ("shield wall",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shield block"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rend(PlayerbotAI* ai)
    {
        return new ActionNode ("rend",
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* revenge(PlayerbotAI* ai)
    {
        return new ActionNode ("revenge",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* devastate(PlayerbotAI* ai)
    {
        return new ActionNode ("devastate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sunder armor"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* shockwave(PlayerbotAI* ai)
    {
        return new ActionNode ("shockwave",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("cleave"), NULL),
            /*C*/ NULL);
    }
};

TankWarriorStrategy::TankWarriorStrategy(PlayerbotAI* ai) : GenericWarriorStrategy(ai)
{
    actionNodeFactories.Add(new TankWarriorStrategyActionNodeFactory());
}

NextAction** TankWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), new NextAction("devastate", 10.0f), new NextAction("revenge", 10.0f), NULL);
}

void TankWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium rage available",
        NextAction::array(0, new NextAction("shield slam", 21.0f), new NextAction("heroic strike", 1.3f), NULL)));

    triggers.push_back(new TriggerNode(
        "light rage available",
        NextAction::array(0, new NextAction("devastate", 1.4f), NULL)));

    triggers.push_back(new TriggerNode(
        "disarm",
        NextAction::array(0, new NextAction("disarm", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("taunt", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("shield wall", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("last stand", 91.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe",
		NextAction::array(0, new NextAction("shockwave", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"light aoe",
		NextAction::array(0, new NextAction("cleave", 23.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"concussion blow",
		NextAction::array(0, new NextAction("concussion blow", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "sword and board",
        NextAction::array(0, new NextAction("shield slam", 40.0f), NULL)));
}
