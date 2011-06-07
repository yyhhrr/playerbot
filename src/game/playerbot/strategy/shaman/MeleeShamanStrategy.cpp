#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanTriggers.h"
#include "ShamanMultipliers.h"
#include "MeleeShamanStrategy.h"
#include "ShamanActions.h"

using namespace ai;

NextAction** MeleeShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), new NextAction("stormstrike", 10.0f), new NextAction("lava lash", 10.0f), NULL);
}

void MeleeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new ShamanWeaponTrigger(ai), 
        NextAction::array(0, new NextAction("windfury weapon", 22.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new LightningShieldTrigger(ai), 
		NextAction::array(0, new NextAction("lightning shield", 22.0f), NULL)));
}

ActionNode* MeleeShamanStrategy::createAction(const char* name)
{
    ActionNode* node = GenericShamanStrategy::createAction(name);
    if (node)
        return node;

	if (!strcmp("stormstrike", name)) 
	{
		return new ActionNode (new CastStormstrikeAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("lava lash"), NULL), 
			/*C*/ NULL);
	}
	else if (!strcmp("lava lash", name)) 
	{
		return new ActionNode (new CastLavaLashAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
			/*C*/ NULL);
	}
	else if (!strcmp("lightning shield", name)) 
	{
		return new ActionNode (new CastLightningShieldAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}

    return GenericShamanStrategy::createAction(name);
}

