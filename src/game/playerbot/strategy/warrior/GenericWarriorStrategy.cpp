#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GenericWarriorStrategy.h"
#include "WarriorActionFactory.h"

using namespace ai;

ActionFactory* GenericWarriorStrategy::createActionFactory()
{
    return new WarriorActionFactory(ai);
}

void GenericWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "battle shout",
        NextAction::array(0, new NextAction("battle shout", 80.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "rend",
        NextAction::array(0, new NextAction("rend", 1.3f), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("demoralizing shout", 23.0f), new NextAction("thunder clap", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium rage available",
        NextAction::array(0, new NextAction("cleave", 31.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "high aoe",
        NextAction::array(0, new NextAction("challenging shout", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodrage",
        NextAction::array(0, new NextAction("bloodrage", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("shield bash", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("intimidating shout", 90.0f), NULL)));
}


ActionNode* GenericWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("hamstring", name))
    {
        return new ActionNode ("hamstring",
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("shield bash", name))
    {
        return new ActionNode ("shield bash",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("shield block", name))
    {
        return new ActionNode ("shield block",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("bloodrage", name))
    {
        return new ActionNode ("bloodrage",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("defensive stance", name))
    {
        return new ActionNode ("defensive stance",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("battle stance", name))
    {
        return new ActionNode ("battle stance",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("heroic strike", name))
    {
        return new ActionNode ("heroic strike",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("cleave", name))
    {
        return new ActionNode ("cleave",
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
    else if (!strcmp("demoralizing shout", name))
    {
        return new ActionNode ("demoralizing shout",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("challenging shout", name))
    {
        return new ActionNode ("challenging shout",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("shield wall", name))
    {
        return new ActionNode ("shield wall",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("battle shout", name))
    {
        return new ActionNode ("battle shout",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("thunder clap", name))
    {
        return new ActionNode ("thunder clap",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else return CombatStrategy::createAction(name);
}
