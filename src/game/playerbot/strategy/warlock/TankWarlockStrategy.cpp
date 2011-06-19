#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "TankWarlockStrategy.h"

using namespace ai;

NextAction** TankWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void TankWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon voidwalker", 50.0f), NULL)));

}


ActionNode* TankWarlockStrategy::GetAction(string name)
{
    if (name == "summon voidwalker") 
    {
        return new ActionNode ("summon voidwalker",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL), 
            /*C*/ NULL);
    }
    else 
        return GenericWarlockStrategy::GetAction(name);
}


