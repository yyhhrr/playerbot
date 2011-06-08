#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "FeralDruidStrategy.h"

using namespace ai;

void FeralDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("survival instincts", 80.0f), NULL)));
}

ActionNode* FeralDruidStrategy::createAction(const char* name)
{
    if (!strcmp("survival instincts", name)) 
    {
        return new ActionNode ("survival instincts",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rejuvenation"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("thorns", name)) 
    {
        return new ActionNode ("thorns",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure poison", name)) 
    {
        return new ActionNode ("cure poison",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure poison on party", name)) 
    {
        return new ActionNode ("cure poison on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish poison", name)) 
    {
        return new ActionNode ("abolish poison",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish poison on party", name)) 
    {
        return new ActionNode ("abolish poison on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("berserk", name)) 
    {
        return new ActionNode ("berserk",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("tiger's fury", name)) 
    {
        return new ActionNode ("tiger's fury",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    
	else return GenericDruidStrategy::createAction(name);
}

