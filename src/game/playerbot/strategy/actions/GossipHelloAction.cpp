#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GossipHelloAction.h"


using namespace ai;

bool GossipHelloAction::Execute(Event event)
{
    WorldPacket &p = event.getPacket();

    ObjectGuid guid;
    p.rpos(0);
    p >> guid;
    p.rpos(0);

    Creature *pCreature = bot->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_NONE);
    if (!pCreature)
    {
        DEBUG_LOG ("[PlayerbotMgr]: HandleMasterIncomingPacket - Received  CMSG_GOSSIP_HELLO %s not found or you can't interact with him.", guid.GetString().c_str());
        return false;
    }

    GossipMenuItemsMapBounds pMenuItemBounds = sObjectMgr.GetGossipMenuItemsMapBounds(pCreature->GetCreatureInfo()->GossipMenuId);
    if (pMenuItemBounds.first == pMenuItemBounds.second)
        return false;

    bot->GetSession()->HandleGossipHelloOpcode(p);

    ostringstream out; out << "--- " << pCreature->GetName() << " ---";
    ai->TellMaster(out.str());

    GossipMenu& menu = bot->PlayerTalkClass->GetGossipMenu();
    int i = 0, loops = 0;
    set<uint32> alreadyTalked;
    while (i < menu.MenuItemCount() && loops++ < 100)
    {
        GossipMenuItem const& item = menu.GetItem(i);
        ai->TellMaster(item.m_gMessage);
        
        if (item.m_gOptionId < 1000 && item.m_gOptionId != GOSSIP_OPTION_GOSSIP)
        {
            i++;
            continue;
        }

        WorldPacket p1;
        std::string code;
        p1 << guid << menu.GetMenuId() << i << code;
        bot->GetSession()->HandleGossipSelectOptionOpcode(p1);
        
        i = 0;
    }

    bot->TalkedToCreature(pCreature->GetEntry(), pCreature->GetObjectGuid());
    return true;
}
