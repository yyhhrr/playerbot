#include "../../pchdef.h"
#include "../playerbot.h"
#include "ListQuestsActions.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool ListQuestsAction::Execute(Event event)
{
    if (event.getParam() == "completed")
    {
        ListQuests(QUEST_LIST_FILTER_COMPLETED);
    }
    else if (event.getParam() == "incompleted")
    {
        ListQuests(QUEST_LIST_FILTER_INCOMPLETED);
    }
    else if (event.getParam() == "summary")
    {
        ListQuests(QUEST_LIST_FILTER_SUMMARY);
    }
    else
    {
        ListQuests(QUEST_LIST_FILTER_ALL);
    }
    return true;
}

void ListQuestsAction::ListQuests(QuestListFilter filter)
{
    AiSocialManager* socialManager = ai->GetSocialManager();

    bool showIncompleted = filter & QUEST_LIST_FILTER_INCOMPLETED;
    bool showCompleted = filter & QUEST_LIST_FILTER_COMPLETED;

    if (showIncompleted)
        socialManager->TellMaster("--- incomplete quests ---");
    int incompleteCount = ListQuests(false, !showIncompleted);

    if (showCompleted)
        socialManager->TellMaster("--- complete quests ---");
    int completeCount = ListQuests(true, !showCompleted);

    socialManager->TellMaster("--- summary ---");
    std::ostringstream out;
    out << "Total: " << (completeCount + incompleteCount) << " / 25 (incomplete: " << incompleteCount << ", complete: " << completeCount << ")";
    socialManager->TellMaster(out.str().c_str());
}

int ListQuestsAction::ListQuests(bool completed, bool silent)
{
    int count = 0;
    for (uint16 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
    {
        uint32 questId = GetBot()->GetQuestSlotQuestId(slot);
        if (!questId)
            continue;

        Quest const* pQuest = sObjectMgr.GetQuestTemplate(questId);
        bool isCompletedQuest = GetBot()->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE;
        if (completed != isCompletedQuest)
            continue;

        count++;

        if (silent)
            continue;

        std::ostringstream stream;
        stream << " |cFFFFFF00|Hquest:" << questId << ':' << pQuest->GetQuestLevel() << "|h[" << pQuest->GetTitle() << "]|h|r";
        ai->GetSocialManager()->TellMaster(stream.str().c_str());
    }

    return count;
}
