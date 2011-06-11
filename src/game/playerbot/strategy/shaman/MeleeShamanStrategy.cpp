#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "MeleeShamanStrategy.h"

using namespace ai;

NextAction** MeleeShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), new NextAction("stormstrike", 10.0f), new NextAction("lava lash", 10.0f), NULL);
}

void MeleeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", 22.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"lightning shield",
		NextAction::array(0, new NextAction("lightning shield", 22.0f), NULL)));
}

ActionNode* MeleeShamanStrategy::GetAction(const char* name)
{
    ActionNode* node = GenericShamanStrategy::GetAction(name);
    if (node)
        return node;

	if (!strcmp("stormstrike", name))
	{
		return new ActionNode ("stormstrike",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("lava lash"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("lava lash", name))
	{
		return new ActionNode ("lava lash",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("melee"), NULL),
			/*C*/ NULL);
	}
	else if (!strcmp("lightning shield", name))
	{
		return new ActionNode ("lightning shield",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}

    return GenericShamanStrategy::GetAction(name);
}

