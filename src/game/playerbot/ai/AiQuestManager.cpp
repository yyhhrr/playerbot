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
}