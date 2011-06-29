#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "TankPaladinStrategy.h"

using namespace ai;

NextAction** TankPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void TankPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "judgement of light",
        NextAction::array(0, new NextAction("judgement of light", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        "righteous fury",
        NextAction::array(0, new NextAction("righteous fury", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("hammer of the righteous", 26.0f), new NextAction("avenger's shield", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("consecration", 27.0f), new NextAction("holy wrath", 27.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("hand of reckoning", 16.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"holy shield",
		NextAction::array(0, new NextAction("holy shield", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("blessing of sanctuary", 21.0f), NULL)));
}

void TankPaladinStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* TankPaladinStrategy::GetAction(string name)
{
    if (name == "blessing of sanctuary")
    {
        return new ActionNode ("blessing of sanctuary",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blessing of kings"), NULL),
            /*C*/ NULL);
    }
    else return GenericPaladinStrategy::GetAction(name);
}
