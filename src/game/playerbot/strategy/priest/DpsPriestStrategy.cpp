#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "DpsPriestStrategy.h"

using namespace ai;

NextAction** DpsPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("holy fire", 9.0f), new NextAction("mind blast", 10.0f), new NextAction("smite", 5.0f), NULL);
}

void DpsPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    HealPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "devouring plague",
        NextAction::array(0, new NextAction("devouring plague", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no attackers",
        NextAction::array(0, new NextAction("mind flay", 20.0f), NULL)));
}

void DpsPriestStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    HealPriestStrategy::InitMultipliers(multipliers);
}

ActionNode* DpsPriestStrategy::GetAction(string name)
{
    ActionNode* node = HealPriestStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "shadow word: pain")
    {
        return new ActionNode ("shadow word: pain",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "devouring plague")
    {
        return new ActionNode ("devouring plague",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "mind flay")
    {
        return new ActionNode ("mind flay",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "mind blast")
    {
        return new ActionNode ("mind blast",
            /*P*/ NextAction::array(0, new NextAction("shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NextAction::array(0, new NextAction("shoot"), NULL));
    }
    else return HealPriestStrategy::GetAction(name);
}
