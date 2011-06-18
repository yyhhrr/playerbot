#include "../../../pchdef.h"
#include "../../playerbot.h"

#include "HunterMultipliers.h"
#include "DpsHunterStrategy.h"

using namespace ai;

NextAction** DpsHunterStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("explosive shot", 11.0f), new NextAction("auto shot", 10.0f), NULL);
}

void DpsHunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericHunterStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "aspect of the viper", 
        NextAction::array(0, new NextAction("aspect of the viper", 91.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "black arrow", 
        NextAction::array(0, new NextAction("black arrow", 51.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no stings", 
        NextAction::array(0, new NextAction("serpent sting", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana", 
        NextAction::array(0, new NextAction("viper sting", 51.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet", 
        NextAction::array(0, new NextAction("call pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet dead", 
        NextAction::array(0, new NextAction("revive pet", 5.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet low health", 
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hunter's mark", 
        NextAction::array(0, new NextAction("hunter's mark", 52.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "freezing trap", 
        NextAction::array(0, new NextAction("freezing trap", 83.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe", 
        NextAction::array(0, new NextAction("multi-shot", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"high aoe", 
		NextAction::array(0, new NextAction("volley", 20.0f), NULL)));
}

void DpsHunterStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    GenericHunterStrategy::InitMultipliers(multipliers);
}

ActionNode* DpsHunterStrategy::GetAction(const char* name)
{
    ActionNode* node = GenericHunterStrategy::GetAction(name);
    if (node)
        return node;

    if (!strcmp("auto shot", name)) 
    {
        return new ActionNode ("auto shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aimed shot", name)) 
    {
        return new ActionNode ("aimed shot",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane shot", 10.0f), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("explosive shot", name)) 
    {
        return new ActionNode ("explosive shot",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aimed shot"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("arcane shot", name)) 
    {
        return new ActionNode ("arcane shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("concussive shot", name)) 
    {
        return new ActionNode ("concussive shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("wyvern sting", 11.0f), NULL));
    }
    else if (!strcmp("distracting shot", name)) 
    {
        return new ActionNode ("distracting shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("multi-shot", name)) 
    {
        return new ActionNode ("multi-shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("volley", name)) 
	{
		return new ActionNode ("volley",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("serpent sting", name)) 
    {
        return new ActionNode ("serpent sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("wyvern sting", name)) 
    {
        return new ActionNode ("wyvern sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("viper sting", name)) 
    {
        return new ActionNode ("viper sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("scorpid sting", name)) 
    {
        return new ActionNode ("scorpid sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("hunter's mark", name)) 
    {
        return new ActionNode ("hunter's mark",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mend pet", name)) 
    {
        return new ActionNode ("mend pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("revive pet", name)) 
    {
        return new ActionNode ("revive pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("black arrow", name)) 
    {
        return new ActionNode ("black arrow",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("freezing trap", name)) 
    {
        return new ActionNode ("freezing trap",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return GenericHunterStrategy::GetAction(name);
}

