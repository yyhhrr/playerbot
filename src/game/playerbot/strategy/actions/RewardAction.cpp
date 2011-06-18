#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RewardAction.h"
#include "../ItemVisitors.h"
#include "../values/ItemCountValue.h"

using namespace ai;

bool RewardAction::Execute(Event event)
{
    string link = event.getParam().c_str();

    ItemIds itemIds = chat->parseItems(link);
    if (itemIds.empty()) 
        return false;

    uint32 itemId = *itemIds.begin();
    bool wasRewarded = false;
    const ObjectGuid &questRewarder = master->GetSelectionGuid();
    uint64 questRewarderGUID = master->GetSelectionGuid().GetRawValue();
    bot->SetSelectionGuid(questRewarder);
    Object* pNpc = ai->GetGameObject(questRewarder);
    if (!pNpc)
        pNpc = ObjectAccessor::GetUnit(*bot, questRewarder);

    if (!pNpc)
        return false;

    QuestMenu& questMenu = bot->PlayerTalkClass->GetQuestMenu();
    for (uint32 iI = 0; !wasRewarded && iI < questMenu.MenuItemCount(); ++iI)
    {
        QuestMenuItem const& qItem = questMenu.GetItem(iI);

        uint32 questID = qItem.m_qId;
        Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);
        QuestStatus status = bot->GetQuestStatus(questID);

        // if quest is complete, turn it in
        if (status == QUEST_STATUS_COMPLETE && 
            ! bot->GetQuestRewardStatus(questID) && 
            pQuest->GetRewChoiceItemsCount() > 1 &&
            bot->CanRewardQuest(pQuest, false))
        {
            for (uint8 rewardIdx=0; !wasRewarded && rewardIdx < pQuest->GetRewChoiceItemsCount(); ++rewardIdx)
            {
                ItemPrototype const * const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
                if (itemId == pRewardItem->ItemId)
                {
                    bot->RewardQuest(pQuest, rewardIdx, pNpc, false);

                    string questTitle  = pQuest->GetTitle();
                    string itemName = pRewardItem->Name1;

                    ostringstream out; out << chat->formatItem(pRewardItem) << " rewarded";
                    ai->TellMaster(out);
                    wasRewarded = true;
                }
            }
        }
    }

    return true;
}
