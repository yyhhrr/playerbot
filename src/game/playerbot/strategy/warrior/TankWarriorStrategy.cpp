#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "TankWarriorStrategy.h"

using namespace ai;

NextAction** TankWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
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
		"concussion blow",
		NextAction::array(0, new NextAction("concussion blow", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "sword and board",
        NextAction::array(0, new NextAction("shield slam", 40.0f), NULL)));
}

void TankWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* TankWarriorStrategy::GetAction(string name)
{
    if (name == "melee")
    {
        return new ActionNode ("melee",
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), new NextAction("reach melee"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "shield wall")
    {
        return new ActionNode ("shield wall",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shield block"), NULL),
            /*C*/ NULL);
    }
    else if (name == "rend")
    {
        return new ActionNode ("rend",
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "revenge")
    {
        return new ActionNode ("revenge",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("slam"), NULL),
            /*C*/ NULL);
    }
    else if (name == "devastate")
    {
        return new ActionNode ("devastate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sunder armor"), NULL),
            /*C*/ NextAction::array(0, new NextAction("revenge", 10.0f), NULL));
    }
    else return GenericWarriorStrategy::GetAction(name);
}
