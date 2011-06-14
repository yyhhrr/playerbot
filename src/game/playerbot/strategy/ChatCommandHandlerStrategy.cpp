#include "../../pchdef.h"
#include "../playerbot.h"
#include "ChatCommandHandlerStrategy.h"

using namespace ai;

void ChatCommandHandlerStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    PassTroughStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rep", 
        NextAction::array(0, new NextAction("reputation", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "q", 
        NextAction::array(0, 
            new NextAction("query quest", relevance), 
            new NextAction("query quest item", relevance), 
            new NextAction("query item usage", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "add all loot", 
        NextAction::array(0, new NextAction("add all loot", relevance), new NextAction("loot", relevance), NULL)));
}

ChatCommandHandlerStrategy::ChatCommandHandlerStrategy(AiManagerRegistry* const ai) : PassTroughStrategy(ai)
{
    supported.push_back("quests");
    supported.push_back("stats");
    supported.push_back("leave");
    supported.push_back("reputation");
    supported.push_back("log");
    supported.push_back("los");
    supported.push_back("drop");
    supported.push_back("ll");
    supported.push_back("release");
    supported.push_back("teleport");
    supported.push_back("taxi");
    supported.push_back("repair");
}
