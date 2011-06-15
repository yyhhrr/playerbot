#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GossipHelloAction.h"


using namespace ai;

bool GossipHelloAction::Execute(Event event)
{
    Player* bot = ai->GetBot();
    Player *master = ai->GetMaster();
    WorldPacket &p = event.getPacket();

    ObjectGuid guid;
    p.rpos(0);                //reset packet pointer
    p >> guid;

    Creature *pCreature = bot->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_NONE);
    if (!pCreature)
    {
        DEBUG_LOG ("[PlayerbotMgr]: HandleMasterIncomingPacket - Received  CMSG_GOSSIP_HELLO %s not found or you can't interact with him.", guid.GetString().c_str());
        return false;
    }

    GossipMenuItemsMapBounds pMenuItemBounds = sObjectMgr.GetGossipMenuItemsMapBounds(pCreature->GetCreatureInfo()->GossipMenuId);
    if (pMenuItemBounds.first == pMenuItemBounds.second)
        return false;

    ostringstream out; out << "--- " << pCreature->GetName() << " ---";
    ai->TellMaster(out.str().c_str());
    for (GossipMenuItemsMap::const_iterator itr = pMenuItemBounds.first; itr != pMenuItemBounds.second; ++itr)
    {
        uint32 npcflags = pCreature->GetUInt32Value(UNIT_NPC_FLAGS);
        if (!(itr->second.npc_option_npcflag & npcflags))
            continue;

        ai->TellMaster(itr->second.option_text.c_str());

        switch (itr->second.option_id)
        {
        case GOSSIP_OPTION_TAXIVENDOR:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_TAXIVENDOR");
                bot->GetSession()->SendLearnNewTaxiNode(pCreature);
                break;
            }
        case GOSSIP_OPTION_QUESTGIVER:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_QUESTGIVER");
                break;
            }
        case GOSSIP_OPTION_VENDOR:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_VENDOR");
                break;
            }
        case GOSSIP_OPTION_STABLEPET:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_STABLEPET");
                break;
            }
        case GOSSIP_OPTION_AUCTIONEER:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_AUCTIONEER");
                break;
            }
        case GOSSIP_OPTION_BANKER:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_BANKER");
                break;
            }
        case GOSSIP_OPTION_INNKEEPER:
            {
                // bot->GetPlayerbotAI()->ai->TellMaster("PlayerbotMgr:GOSSIP_OPTION_INNKEEPER");
                break;
            }
        }
    }
    return true;
}
