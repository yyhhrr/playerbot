#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AcceptQuestAction.h"


using namespace ai;

bool AcceptQuestAction::Execute(Event event)
{
    Player *bot = ai->GetBot();
    uint64 guid;
    uint32 quest;

    string text = event.getParam();
    PlayerbotChatHandler ch(master);
    quest = ch.extractQuestId(text);
    if (quest)
    {
        guid = master->GetSelectionGuid().GetRawValue();
        if (!guid)
        {
            ai->TellMaster("Please select questgiver first");
            return false;
        }
    }
    else if (!event.getPacket().empty())
    {
        WorldPacket& p = event.getPacket();
        p.rpos(0);
        p >> guid >> quest;
    }
    else
        return false;

    Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);
    if (qInfo)
    {
        if (bot->GetQuestStatus(quest) == QUEST_STATUS_COMPLETE)
            ai->TellMaster("I already completed that quest.");
        else if (! bot->CanTakeQuest(qInfo, false))
        {                    	
            if (! bot->SatisfyQuestStatus(qInfo, false))
                ai->TellMaster("I already have that quest.");
            else
                ai->TellMaster("I can't take that quest.");
        }
        else if (! bot->SatisfyQuestLog(false))
            ai->TellMaster("My quest log is full.");
        else if (! bot->CanAddQuest(qInfo, false))
            ai->TellMaster("I can't take that quest because it requires that I take items, but my bags are full!");

        else
        {
            WorldPacket p(CMSG_QUESTGIVER_ACCEPT_QUEST);
            uint32 unk1 = 0;
            p << guid << quest << unk1;
            p.rpos(0);
            bot->GetSession()->HandleQuestgiverAcceptQuestOpcode(p);

            if (bot->GetQuestStatus(quest) != QUEST_STATUS_NONE && bot->GetQuestStatus(quest) != QUEST_STATUS_AVAILABLE)
                ai->TellMaster("Got the quest.");
        }
    }

    return false;
}

bool AcceptQuestShareAction::Execute(Event event)
{
    
    Player *bot = ai->GetBot();

    WorldPacket& p = event.getPacket();
    p.rpos(0);
    uint64 skip;
    uint64 guid;
    uint32 quest;
    p >> guid >> skip >> quest;
    Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);

    if (!qInfo || !bot->GetDividerGuid())
        return false;

    quest = qInfo->GetQuestId();
    if( !bot->CanTakeQuest( qInfo, false ) )
    {
        // can't take quest
        bot->SetDividerGuid( ObjectGuid() );
        ai->TellMaster("I can't take this quest");

        return false;
    }

    if( !bot->GetDividerGuid().IsEmpty() )
    {
        // send msg to quest giving player
        master->SendPushToPartyResponse( bot, QUEST_PARTY_MSG_ACCEPT_QUEST );
        bot->SetDividerGuid( ObjectGuid() );
    }

    if( bot->CanAddQuest( qInfo, false ) )
    {
        bot->AddQuest( qInfo, master );

        if( bot->CanCompleteQuest( quest ) )
            bot->CompleteQuest( quest );

        // Runsttren: did not add typeid switch from WorldSession::HandleQuestgiverAcceptQuestOpcode!
        // I think it's not needed, cause typeid should be TYPEID_PLAYER - and this one is not handled
        // there and there is no default case also.

        if( qInfo->GetSrcSpell() > 0 )
            bot->CastSpell( bot, qInfo->GetSrcSpell(), true );

        ai->TellMaster("Quest accepted");
        return true;
    }

    return false;
}
