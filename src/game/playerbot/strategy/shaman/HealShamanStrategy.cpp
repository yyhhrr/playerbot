#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanTriggers.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"
#include "ShamanActions.h"

using namespace ai;

NextAction** HealShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void HealShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new ShamanWeaponTrigger(ai), 
        NextAction::array(0, new NextAction("earthliving weapon", 22.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new BuffTrigger(ai, "water shield"), 
		NextAction::array(0, new NextAction("water shield", 22.0f), NULL)));
}

ActionNode* HealShamanStrategy::createAction(const char* name)
{
    ActionNode* node = GenericShamanStrategy::createAction(name);
    if (node)
        return node;
	
	if (!strcmp("earthliving weapon", name)) 
	{
		return new ActionNode (new CastEarthlivingWeaponAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("flametongue weapon"), NULL), 
			/*C*/ NULL);
	}

    return NULL;
}

