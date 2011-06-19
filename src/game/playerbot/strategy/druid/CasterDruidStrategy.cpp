#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "CasterDruidStrategy.h"

using namespace ai;


NextAction** CasterDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("starfire", 11.0f), new NextAction("wrath", 10.0f), NULL);
}

void CasterDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"insect swarm",
		NextAction::array(0, new NextAction("insect swarm", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"moonfire",
		NextAction::array(0, new NextAction("moonfire", 14.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"faerie fire",
		NextAction::array(0, new NextAction("faerie fire", 16.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"nature's grasp",
		NextAction::array(0, new NextAction("nature's grasp", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"high aoe",
		NextAction::array(0, new NextAction("starfall", 17.0f), NULL)));
}

void CasterDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* CasterDruidStrategy::GetAction(string name)
{
    if (name == "faerie fire")
    {
        return new ActionNode ("faerie fire",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (name == "reach spell")
	{
		return new ActionNode ("reach spell",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (name == "flee")
	{
		return new ActionNode ("flee",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (name == "moonkin form")
    {
        return new ActionNode ("moonkin form",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	else if (name == "hibernate")
	{
		return new ActionNode ("hibernate",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NextAction::array(0, new NextAction("entangling roots"), NULL),
			/*C*/ NextAction::array(0, new NextAction("flee", 49.0f), NULL));
	}
	else if (name == "entangling roots")
	{
		return new ActionNode ("entangling roots",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NextAction::array(0, new NextAction("flee", 49.0f), NULL));
	}
    else if (name == "entangling roots on cc")
    {
        return new ActionNode ("entangling roots on cc",
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (name == "wrath")
	{
		return new ActionNode ("wrath",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else if (name == "starfall")
	{
		return new ActionNode ("starfall",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (name == "insect swarm")
	{
		return new ActionNode ("insect swarm",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (name == "moonfire")
	{
		return new ActionNode ("moonfire",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (name == "starfire")
	{
		return new ActionNode ("starfire",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
	else if (name == "nature's grasp")
	{
		return new ActionNode ("nature's grasp",
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL,
			/*C*/ NULL);
	}
    else return GenericDruidStrategy::GetAction(name);
}
