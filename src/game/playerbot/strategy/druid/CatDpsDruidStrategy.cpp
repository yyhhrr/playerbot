#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "CatDpsDruidStrategy.h"

using namespace ai;


NextAction** CatDpsDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("mangle (cat)", 10.0f), NULL);
}

void CatDpsDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    FeralDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("melee", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "rake",
        NextAction::array(0, new NextAction("rake", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "combo points available",
        NextAction::array(0, new NextAction("ferocious bite", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("cower", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"tiger's fury",
		NextAction::array(0, new NextAction("tiger's fury", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("swipe (cat)", 30.0f), NULL)));
}

void CatDpsDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* CatDpsDruidStrategy::GetAction(string name)
{
    if (name == "reach melee")
    {
        return new ActionNode ("reach melee",
            /*P*/ NextAction::array(0, new NextAction("cat form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "faerie fire (feral)")
    {
        return new ActionNode ("faerie fire (feral)",
            /*P*/ NextAction::array(0, new NextAction("cat form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (name == "melee")
    {
        return new ActionNode ("melee",
            /*P*/ NextAction::array(0, new NextAction("cat form"), new NextAction("feral charge - cat"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "feral charge - cat")
    {
        return new ActionNode ("feral_charge_cat",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*C*/ NULL);
    }
    else if (name == "cat form")
    {
        return new ActionNode ("cat form",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (name == "claw")
    {
        return new ActionNode ("claw",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("claw", 15.0f), NULL));
    }
    else if (name == "mangle (cat)")
    {
        return new ActionNode ("mangle (cat)",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("claw"), NULL),
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 15.0f), NULL));
    }
    else if (name == "swipe (cat)")
    {
        return new ActionNode ("swipe (cat)",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "rake")
    {
        return new ActionNode ("rake",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 15.0f), NULL));
    }
    else if (name == "ferocious bite")
    {
        return new ActionNode ("ferocious bite",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rip"), NULL),
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 10.0f), NULL));
    }
    else if (name == "rip")
    {
        return new ActionNode ("rip",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 10.0f), NULL));
    }
    else if (name == "cower")
    {
        return new ActionNode ("cower",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else return FeralDruidStrategy::GetAction(name);
}
