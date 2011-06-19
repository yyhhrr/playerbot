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

ActionNode* DpsHunterStrategy::GetAction(string name)
{
    ActionNode* node = GenericHunterStrategy::GetAction(name);
    if (node)
        return node;

    if (name == "auto shot") 
    {
        return new ActionNode ("auto shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "aimed shot") 
    {
        return new ActionNode ("aimed shot",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane shot", 10.0f), NULL), 
            /*C*/ NULL);
    }
    else if (name == "explosive shot") 
    {
        return new ActionNode ("explosive shot",  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aimed shot"), NULL), 
            /*C*/ NULL);
    }
    else if (name == "arcane shot") 
    {
        return new ActionNode ("arcane shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "concussive shot") 
    {
        return new ActionNode ("concussive shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("wyvern sting", 11.0f), NULL));
    }
    else if (name == "distracting shot") 
    {
        return new ActionNode ("distracting shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "multi-shot") 
    {
        return new ActionNode ("multi-shot",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (name == "volley") 
	{
		return new ActionNode ("volley",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (name == "serpent sting") 
    {
        return new ActionNode ("serpent sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "wyvern sting") 
    {
        return new ActionNode ("wyvern sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "viper sting") 
    {
        return new ActionNode ("viper sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "scorpid sting") 
    {
        return new ActionNode ("scorpid sting",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "hunter's mark") 
    {
        return new ActionNode ("hunter's mark",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "mend pet") 
    {
        return new ActionNode ("mend pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "revive pet") 
    {
        return new ActionNode ("revive pet",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "black arrow") 
    {
        return new ActionNode ("black arrow",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (name == "freezing trap") 
    {
        return new ActionNode ("freezing trap",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return GenericHunterStrategy::GetAction(name);
}

