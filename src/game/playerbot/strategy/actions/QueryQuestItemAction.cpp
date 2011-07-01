#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "QueryQuestItemAction.h"


using namespace ai;


bool QueryQuestItemAction::Execute(Event event)
{
    Player *bot = ai->GetBot();
    string text = event.getParam();

    ItemIds items = chat->parseItems(text);

    for (ItemIds::iterator i = items.begin(); i != items.end(); i++)
        QueryQuestItem(*i);

    return false;
}

void QueryQuestItemAction::QueryQuestItem(uint32 itemId) 
{
    Player *bot = ai->GetBot();
    QuestStatusMap& questMap = bot->getQuestStatusMap();
    for (QuestStatusMap::iterator i = questMap.begin(); i != questMap.end(); i++)
    {
        const Quest *questTemplate = sObjectMgr.GetQuestTemplate( i->first );
        if( !questTemplate )
            continue;

        QuestStatus status = bot->GetQuestStatus(questTemplate->GetQuestId());
        if (status != QUEST_STATUS_INCOMPLETE && status != QUEST_STATUS_COMPLETE)
            continue;

        QuestStatusData *questStatus = &i->second;
        QueryQuestItem(itemId, questTemplate, questStatus);
    }    
}


void QueryQuestItemAction::QueryQuestItem(uint32 itemId, const Quest *questTemplate, QuestStatusData *questStatus)
{
    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
    {
        if (questTemplate->ReqItemId[i] != itemId)
            continue;

        int required = questTemplate->ReqItemCount[i];
        int available = questStatus->m_itemcount[i];

        if (!required)
            continue;

        ostringstream out;
        out << "Quest ";
        out << available;
        out << "/";
        out << required;
        ai->TellMaster(out.str());
    }
}

