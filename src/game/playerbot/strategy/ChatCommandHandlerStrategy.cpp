#include "../../pchdef.h"
#include "../playerbot.h"
#include "ChatCommandHandlerStrategy.h"

using namespace ai;

ActionNode* ChatCommandHandlerStrategy::createAction(const char* name)
{
    return new ActionNode(name,  
        /*P*/ NULL,
        /*A*/ NULL, 
        /*C*/ NULL);
}

void ChatCommandHandlerStrategy::InitTriggers(std::list<TriggerNode*> &triggers) 
{
    triggers.push_back(new TriggerNode(
        "quests", 
        NextAction::array(0, new NextAction("quests", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "stats", 
        NextAction::array(0, new NextAction("stats", 100.0f), NULL)));
}
