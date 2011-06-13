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

    PlayerbotChatHandler ch(master);
    uint32 questId = ch.extractQuestId(text.c_str());
    if (!questId)
        return false;

    for (uint16 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        if(questId == bot->GetQuestSlotQuestId(slot))
        {
            ostringstream out;
            out << "Quest ";
            out << (bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE ? "completed" : "not completed");
            TellMaster(out.str().c_str());
            return true;
        }
    }

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
        if( questStatus->m_status != QUEST_STATUS_INCOMPLETE )
            continue;

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

        if (!required || available >= required)
            continue;

        ostringstream out;
        out << "Quest ";
        out << available;
        out << "/";
        out << required;
        TellMaster(out.str().c_str());
    }
}

