#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "TankWarriorStrategy.h"

using namespace ai;

NextAction** TankWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void TankWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium rage available", 
        NextAction::array(0, new NextAction("shield slam", 21.0f), new NextAction("heroic strike", 1.3f), NULL)));

    triggers.push_back(new TriggerNode(
        "light rage available", 
        NextAction::array(0, new NextAction("devastate", 1.4f), NULL)));

    triggers.push_back(new TriggerNode(
        "disarm", 
        NextAction::array(0, new NextAction("disarm", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro", 
        NextAction::array(0, new NextAction("taunt", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health", 
        NextAction::array(0, new NextAction("shield wall", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health", 
		NextAction::array(0, new NextAction("last stand", 91.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe", 
		NextAction::array(0, new NextAction("shockwave", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"concussion blow", 
		NextAction::array(0, new NextAction("concussion blow", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "sword and board", 
        NextAction::array(0, new NextAction("shield slam", 40.0f), NULL)));
}

void TankWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* TankWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("melee", name)) 
    {
        return new ActionNode ("melee",  
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shield wall", name)) 
    {
        return new ActionNode ("shield wall",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shield block"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("rend", name)) 
    {
        return new ActionNode ("rend",  
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("taunt", name)) 
    {
        return new ActionNode ("taunt",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("revenge", name)) 
    {
        return new ActionNode ("revenge",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("slam"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("slam", name)) 
    {
        return new ActionNode ("slam",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("shield slam", name)) 
	{
		return new ActionNode ("shield slam",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("disarm", name)) 
    {
        return new ActionNode ("disarm",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("sunder armor", name)) 
    {
        return new ActionNode ("sunder armor",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("devastate", name)) 
    {
        return new ActionNode ("devastate",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sunder armor"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("revenge", 10.0f), NULL));
    }
    else if (!strcmp("shield bash", name)) 
    {
        return new ActionNode ("shield bash",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("intimidating shout", name)) 
    {
        return new ActionNode ("intimidating shout",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("last stand", name)) 
	{
		return new ActionNode ("last stand",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("shockwave", name)) 
	{
		return new ActionNode ("shockwave",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("concussion blow", name)) 
	{
		return new ActionNode ("concussion blow",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return GenericWarriorStrategy::createAction(name);
}