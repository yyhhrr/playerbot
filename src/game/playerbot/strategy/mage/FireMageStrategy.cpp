#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "FireMageStrategy.h"

using namespace ai;

NextAction** FireMageStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("fire blast", 1.0f), new NextAction("scorch", 1.0f), NULL);
}

void FireMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fireball", 
        NextAction::array(0, new NextAction("fireball", 5.0f), NULL)));
    triggers.push_back(new TriggerNode(
        "pyroblast", 
        NextAction::array(0, new NextAction("pyroblast", 10.0f), NULL)));
    triggers.push_back(new TriggerNode(
        "hot streak",
        NextAction::array(0, new NextAction("pyroblast", 25.0f), NULL)));
    triggers.push_back(new TriggerNode(
        "combustion",
        NextAction::array(0, new NextAction("combustion", 50.0f), NULL)));
    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("flamestrike", 20.0f), NULL)));
}

