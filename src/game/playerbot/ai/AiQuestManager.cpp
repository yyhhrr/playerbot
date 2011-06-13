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

void AiQuestManager::Query(const string& text)
{

 
}

void AiQuestManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
}