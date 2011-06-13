#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

void AiQuestManager::QuestLocalization(string& questTitle, const uint32 questID)
{
	int loc = ai->GetMaster()->GetSession()->GetSessionDbLocaleIndex();
	wstring wnamepart;

	QuestLocale const *pQuestInfo = sObjectMgr.GetQuestLocale(questID);
	if (pQuestInfo)
	{
		if (pQuestInfo->Title.size() > loc && !pQuestInfo->Title[loc].empty())
		{
			const string title = pQuestInfo->Title[loc];
			if (Utf8FitTo(title, wnamepart))
				questTitle = title.c_str();
		}
	}
}



void AiQuestManager::AcceptQuest( Quest const *qInfo, Player *pGiver )
{
	if( !qInfo || !pGiver )
		return;

	uint32 quest = qInfo->GetQuestId();
	if( !bot->CanTakeQuest( qInfo, false ) )
	{
		// can't take quest
		bot->SetDividerGuid( ObjectGuid() );
        aiRegistry->GetSocialManager()->TellMaster("I can't take this quest");

		return;
	}

	if( !bot->GetDividerGuid().IsEmpty() )
	{
		// send msg to quest giving player
		pGiver->SendPushToPartyResponse( bot, QUEST_PARTY_MSG_ACCEPT_QUEST );
		bot->SetDividerGuid( ObjectGuid() );
	}

	if( bot->CanAddQuest( qInfo, false ) )
	{
		bot->AddQuest( qInfo, pGiver );

		if( bot->CanCompleteQuest( quest ) )
			bot->CompleteQuest( quest );

		// Runsttren: did not add typeid switch from WorldSession::HandleQuestgiverAcceptQuestOpcode!
		// I think it's not needed, cause typeid should be TYPEID_PLAYER - and this one is not handled
		// there and there is no default case also.

		if( qInfo->GetSrcSpell() > 0 )
			bot->CastSpell( bot, qInfo->GetSrcSpell(), true );

        aiRegistry->GetSocialManager()->TellMaster("Quest accepted");
	}
}

void AiQuestManager::HandleCommand(const string& text, Player& fromPlayer)
{
}

void AiQuestManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{

}

void AiQuestManager::QueryQuestItem(uint32 itemId, const Quest *questTemplate, QuestStatusData *questStatus)
{
    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
    {
        if (questTemplate->ReqItemId[i] != itemId)
            continue;

        int required = questTemplate->ReqItemCount[i];
        int available = questStatus->m_itemcount[i];

        if (!required || available >= required)
            continue;

        ostringstream out;
        out << "Quest ";
        out << available;
        out << "/";
        out << required;
        aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
    }
}

void AiQuestManager::QueryQuestItem(uint32 itemId) 
{
    QuestStatusMap& questMap = bot->getQuestStatusMap();
    for (QuestStatusMap::iterator i = questMap.begin(); i != questMap.end(); i++)
    {
        const Quest *questTemplate = sObjectMgr.GetQuestTemplate( i->first );
        if( !questTemplate )
            continue;

        QuestStatusData *questStatus = &i->second;
        if( questStatus->m_status != QUEST_STATUS_INCOMPLETE )
            continue;

        QueryQuestItem(itemId, questTemplate, questStatus);
    }    
}


void AiQuestManager::QueryQuest(uint32 id) 
{
    for (uint16 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        if(id == bot->GetQuestSlotQuestId(slot))
        {
            ostringstream out;
            out << "Quest ";
            out << (bot->GetQuestStatus(id) == QUEST_STATUS_COMPLETE ? "completed" : "not completed");
            aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
            break;
        }
    }
}

void AiQuestManager::Query(const string& text)
{
    list<uint32> items;
    aiRegistry->GetInventoryManager()->extractItemIds(text, items);

    for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
        QueryQuestItem(*i);

 
    PlayerbotChatHandler ch(ai->GetMaster());
    uint32 questId = ch.extractQuestId(text.c_str());
    if (questId)
        QueryQuest(questId);
}

void AiQuestManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
	case CMSG_QUESTGIVER_ACCEPT_QUEST:
		{
			WorldPacket p(packet);
			p.rpos(0);
			uint64 guid;
			uint32 quest;
			p >> guid >> quest;
			Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);
			if (qInfo)
			{
				if (bot->GetQuestStatus(quest) == QUEST_STATUS_COMPLETE)
					bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I already completed that quest.");
				else if (! bot->CanTakeQuest(qInfo, false))
				{                    	
					if (! bot->SatisfyQuestStatus(qInfo, false))
						bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I already have that quest.");
					else
						bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I can't take that quest.");
				}
				else if (! bot->SatisfyQuestLog(false))
					bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("My quest log is full.");
				else if (! bot->CanAddQuest(qInfo, false))
					bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I can't take that quest because it requires that I take items, but my bags are full!");

				else
				{
					p.rpos(0);
					bot->GetSession()->HandleQuestgiverAcceptQuestOpcode(p);
					bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("Got the quest.");
				}
			}
		}
		break;
	}
}