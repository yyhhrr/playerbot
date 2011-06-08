#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "BearTankDruidStrategy.h"

using namespace ai;

NextAction** BearTankDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void BearTankDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    FeralDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "thorns",
        NextAction::array(0, new NextAction("thorns", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("growl", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "light rage available",
        NextAction::array(0, new NextAction("mangle (bear)", 20.0f), new NextAction("maul", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "high rage available",
        NextAction::array(0, new NextAction("swipe (bear)", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("demoralizing roar", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("swipe (bear)", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "bash",
        NextAction::array(0, new NextAction("bash", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", 30.0f), NULL)));
}

void BearTankDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* BearTankDruidStrategy::createAction(const char* name)
{
    if (!strcmp("melee", name))
    {
        return new ActionNode ("melee",
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), new NextAction("feral charge - bear"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("feral charge - bear", name))
    {
        return new ActionNode ("feral charge - bear",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*C*/ NULL);
    }
    else if (!strcmp("swipe (bear)", name))
    {
        return new ActionNode ("swipe (bear)",
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("faerie fire (feral)", name))
    {
        return new ActionNode ("faerie fire (feral)",
			/*P*/ NextAction::array(0, new NextAction("dire bear form"), new NextAction("feral charge - bear"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("bear form", name))
    {
        return new ActionNode ("bear form",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("dire bear form", name))
    {
        return new ActionNode ("dire bear form",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("mangle (bear)", name))
    {
        return new ActionNode ("mangle (bear)",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("maul"), NULL),
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("maul", name))
    {
        return new ActionNode ("maul",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("bash", name))
    {
        return new ActionNode ("bash",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("swipe", name))
    {
        return new ActionNode ("swipe",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("growl", name))
    {
        return new ActionNode ("growl",
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), new NextAction("reach spell"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("demoralizing roar", name))
    {
        return new ActionNode ("demoralizing roar",
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else return FeralDruidStrategy::createAction(name);
}
