#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericDruidStrategy.h"
#include "DruidAiObjectContext.h"

using namespace ai;

AiObjectContext* GenericDruidStrategy::createAiObjectContext() 
{
    return new DruidAiObjectContext(ai); 
}

void GenericDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"medium health",
		NextAction::array(0, new NextAction("regrowth", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("rejuvenation", 70.0f), new NextAction("healing touch", 70.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member medium health",
		NextAction::array(0, new NextAction("regrowth on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("rejuvenation on party", 70.0f), new NextAction("healing touch on party", 70.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("rebirth", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", 31.0f), NULL)));
}

ActionNode* GenericDruidStrategy::GetAction(string name)
{
    if (name == "melee") 
    {
        return new ActionNode ("melee",  
            /*P*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "caster form") 
    {
        return new ActionNode ("caster form",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "gift of the naaru") 
    {
        return new ActionNode ("gift of the naaru",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("regrowth"), NULL), 
            /*C*/ NULL);
    }
    else if (name == "regrowth") 
    {
        return new ActionNode ("regrowth",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (name == "rejuvenation") 
    {
        return new ActionNode ("rejuvenation",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "healing touch") 
    {
        return new ActionNode ("healing touch",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "regrowth on party") 
    {
        return new ActionNode ("regrowth on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (name == "rejuvenation on party") 
    {
        return new ActionNode ("rejuvenation on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "healing touch on party") 
    {
        return new ActionNode ("healing touch on party",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "cure poison") 
    {
        return new ActionNode ("cure poison",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "cure poison on party") 
    {
        return new ActionNode ("cure poison on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "abolish poison") 
    {
        return new ActionNode ("abolish poison",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "abolish poison on party") 
    {
        return new ActionNode ("abolish poison on party",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (name == "rebirth") 
	{
		return new ActionNode ("rebirth",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (name == "entangling roots on cc") 
    {
        return new ActionNode ("entangling roots on cc",  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }

    else return Strategy::GetAction(name);
}
