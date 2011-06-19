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

ActionNode* FeralDruidStrategy::GetAction(string name)
{
    if (name == "survival instincts") 
    {
        return new ActionNode ("survival instincts",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rejuvenation"), NULL), 
            /*C*/ NULL);
    }
    else if (name == "thorns") 
    {
        return new ActionNode ("thorns",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "cure poison") 
    {
        return new ActionNode ("cure poison",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "cure poison on party") 
    {
        return new ActionNode ("cure poison on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "abolish poison") 
    {
        return new ActionNode ("abolish poison",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "abolish poison on party") 
    {
        return new ActionNode ("abolish poison on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "berserk") 
    {
        return new ActionNode ("berserk",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "tiger's fury") 
    {
        return new ActionNode ("tiger's fury",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    
	else return GenericDruidStrategy::GetAction(name);
}

