#include "../../pchdef.h"
#include "../playerbot.h"
#include "QueryQuestItemAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool QueryQuestItemAction::Execute(Event event)
{
    Player *master = ai->GetAi()->GetMaster();
    Player *bot = ai->GetAi()->GetBot();
    string text = event.getParam();

    list<uint32> items;
    ai->GetInventoryManager()->extractItemIds(text, items);

    for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
        QueryQuestItem(*i);

    return false;
}

void QueryQuestItemAction::QueryQuestItem(uint32 itemId) 
{
    Player *bot = ai->GetAi()->GetBot();
    QuestStatusMap& questMap = bot->getQuestStatusMap();
    for (QuestStatusMap::iterator i = questMap.begin(); i != questMap.end(); i++)
    {
        const Quest *questTemplate = sObjectMgr.GetQuestTemplate( i->first );
        if( !questTemplate )
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
        ai->GetAi()->TellMaster(out.str().c_str());
    }
}

