#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"

using namespace ai;

NextAction** HealShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void HealShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", 22.0f), NULL)));

	triggers.push_back(new TriggerNode(
        "water shield",
		NextAction::array(0, new NextAction("water shield", 22.0f), NULL)));
}

ActionNode* HealShamanStrategy::GetAction(const char* name)
{
    ActionNode* node = GenericShamanStrategy::GetAction(name);
    if (node)
        return node;

	if (!strcmp("earthliving weapon", name))
	{
		return new ActionNode ("earthliving weapon",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("flametongue weapon"), NULL),
			/*C*/ NULL);
	}

    return GenericShamanStrategy::GetAction(name);
}

