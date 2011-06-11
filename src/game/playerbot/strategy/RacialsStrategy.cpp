#include "../../pchdef.h"
#include "../playerbot.h"
#include "RacialsStrategy.h"
#include "HealthTriggers.h"
#include "GenericSpellActions.h"
#include "GenericTriggers.h"

using namespace ai;

void RacialsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"low health", 
		NextAction::array(0, new NextAction("lifeblood", 71.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana", 
        NextAction::array(0, new NextAction("arcane torrent", 55.0f), NULL)));
}


ActionNode* RacialsStrategy::GetAction(const char* name)
{
	if (!strcmp("lifeblood", name)) 
	{
		return new ActionNode ("lifeblood",  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("gift of the naaru"), NULL), 
			/*C*/ NULL);
	}
	else if (!strcmp("gift of the naaru", name)) 
	{
		return new ActionNode ("gift of the naaru",  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("arcane torrent", name)) 
    {
        return new ActionNode ("arcane torrent",  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else return Strategy::GetAction(name);
}

