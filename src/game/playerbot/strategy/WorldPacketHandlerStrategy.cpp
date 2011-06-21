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

    triggers.push_back(new TriggerNode(
        "cannot equip", 
        NextAction::array(0, new NextAction("tell cannot equip", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "use game object", 
        NextAction::array(0, 
            new NextAction("talk to quest giver", relevance), 
            new NextAction("add loot", relevance), 
            new NextAction("use meeting stone", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "gossip hello", 
        NextAction::array(0, 
            new NextAction("talk to quest giver", relevance), 
            new NextAction("trainer", relevance), 
            new NextAction("gossip hello", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "complete quest", 
        NextAction::array(0, new NextAction("talk to quest giver", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "quest share", 
        NextAction::array(0, new NextAction("accept quest share", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "activate taxi", 
        NextAction::array(0, new NextAction("remember taxi", relevance), new NextAction("taxi", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "trade status", 
        NextAction::array(0, new NextAction("accept trade", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "area trigger", 
        NextAction::array(0, new NextAction("reach area trigger", relevance), NULL)));

    triggers.push_back(new TriggerNode(
        "within area trigger", 
        NextAction::array(0, new NextAction("area trigger", relevance), NULL)));
}

WorldPacketHandlerStrategy::WorldPacketHandlerStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai)
{
    supported.push_back("accept quest");
    supported.push_back("loot roll");
    supported.push_back("check mount state");
}
