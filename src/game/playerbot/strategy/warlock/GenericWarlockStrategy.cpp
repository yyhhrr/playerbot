#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockStrategy.h"

using namespace ai;

NextAction** GenericWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void GenericWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "curse of agony",
        NextAction::array(0, new NextAction("curse of agony", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("drain life", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"target critical health",
		NextAction::array(0, new NextAction("drain soul", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "banish",
        NextAction::array(0, new NextAction("banish", 21.0f), NULL)));
}


ActionNode* GenericWarlockStrategy::GetAction(string name)
{
    if (name == "summon voidwalker")
    {
        return new ActionNode ("summon voidwalker",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL),
            /*C*/ NULL);
    }
    else return CombatStrategy::GetAction(name);
}


