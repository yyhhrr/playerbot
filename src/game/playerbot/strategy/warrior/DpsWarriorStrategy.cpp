#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "DpsWarriorStrategy.h"

using namespace ai;

NextAction** DpsWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void DpsWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "medium rage available", 
        NextAction::array(0, new NextAction("bloodthirst", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee", 
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro", 
        NextAction::array(0, new NextAction("mocking blow", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health", 
        NextAction::array(0, new NextAction("execute", 60.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"hamstring", 
		NextAction::array(0, new NextAction("hamstring", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"victory rush", 
		NextAction::array(0, new NextAction("victory rush", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "death wish",
        NextAction::array(0, new NextAction("death wish", 40.0f), NULL)));
}

void DpsWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* DpsWarriorStrategy::GetAction(const char* name)
{
    if (!strcmp("overpower", name)) 
    {
        return new ActionNode ("overpower",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("melee", name)) 
    {
        return new ActionNode ("melee",  
            /*P*/ NextAction::array(0, new NextAction("charge"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("charge", name)) 
    {
        return new ActionNode ("charge",  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("bloodthirst", name)) 
    {
        return new ActionNode ("bloodthirst",  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heroic strike"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("rend", name)) 
    {
        return new ActionNode ("rend",  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mocking blow", name)) 
    {
        return new ActionNode ("mocking blow",  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("death wish", name) || !strcmp("boost", name)) 
    {
        return new ActionNode ("death wish",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("berserker rage"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("berserker rage", name)) 
    {
        return new ActionNode ("berserker rage",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("victory rush", name)) 
	{
		return new ActionNode ("victory rush",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("execute", name)) 
    {
        return new ActionNode ("execute",  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heroic strike"), NULL), 
            /*C*/ NULL);
    }
    else return GenericWarriorStrategy::GetAction(name);
}
