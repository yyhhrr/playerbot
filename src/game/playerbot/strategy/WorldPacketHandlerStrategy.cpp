#include "../../pchdef.h"
#include "../playerbot.h"
#include "WorldPacketHandlerStrategy.h"

using namespace ai;

void WorldPacketHandlerStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    PassTroughStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "group invite", 
        NextAction::array(0, new NextAction("accept invitation", relevance), NULL)));
    
    triggers.push_back(new TriggerNode(
        "group set leader", 
        NextAction::array(0, new NextAction("pass leadership to master", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "not enough money", 
        NextAction::array(0, new NextAction("tell not enough money", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "not enough reputation", 
        NextAction::array(0, new NextAction("tell not enough reputation", relevance), NULL)));
}

WorldPacketHandlerStrategy::WorldPacketHandlerStrategy(AiManagerRegistry* const ai) : PassTroughStrategy(ai)
{
    supported.push_back("gossip hello");
}
