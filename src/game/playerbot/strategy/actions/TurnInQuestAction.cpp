#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TurnInQuestAction.h"


using namespace ai;

bool TurnInQuestAction::Execute(Event event)
{
    

    ObjectGuid guid = event.getObject();
    if (!guid)
        return false;

    GameObject *obj = ai->GetGameObject(guid);
    if (obj && obj->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        TurnInQuests(obj);
        return true;
    }

    WorldObject* pNpc = master->GetMap()->GetWorldObject(guid);
    if (pNpc)
    {
        TurnInQuests( pNpc );
        return true;
    }

    return false;
}


void TurnInQuestAction::TurnInQuests(WorldObject *questgiver)
{
    ObjectGuid giverGUID = questgiver->GetObjectGuid();

    if( !bot->IsInMap( questgiver ) )
        ai->TellMaster("hey you are turning in quests without me!");
    else
    {
        bot->SetSelectionGuid( ObjectGuid(giverGUID) );

        // auto complete every completed quest this NPC has
        bot->PrepareQuestMenu( giverGUID );
        QuestMenu& questMenu = bot->PlayerTalkClass->GetQuestMenu();
        for (uint32 iI = 0; iI < questMenu.MenuItemCount(); ++iI)
        {
            QuestMenuItem const& qItem = questMenu.GetItem(iI);
            uint32 questID = qItem.m_qId;
            Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);

            std::ostringstream out;
            std::string questTitle  = pQuest->GetTitle();

            QuestStatus status = bot->GetQuestStatus(questID);

            // if quest is complete, turn it in
            if (status == QUEST_STATUS_COMPLETE)
            {
                // if bot hasn't already turned quest in
                if (! bot->GetQuestRewardStatus(questID))
                {
                    // auto reward quest if no choice in reward
                    if (pQuest->GetRewChoiceItemsCount() == 0)
                    {
                        if (bot->CanRewardQuest(pQuest, false))
                        {
                            bot->RewardQuest(pQuest, 0, questgiver, false);
                            out << "Quest completed: " << chat->formatQuest(pQuest);
                        }
                        else
                        {
                            out << "|cffff0000Unable to turn quest in:|r " << chat->formatQuest(pQuest);
                        }
                    }

                    // auto reward quest if one item as reward
                    else if (pQuest->GetRewChoiceItemsCount() == 1)
                    {
                        int rewardIdx = 0;
                        ItemPrototype const *pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
                        std::string itemName = pRewardItem->Name1;
                        if (bot->CanRewardQuest(pQuest, rewardIdx, false))
                        {
                            bot->RewardQuest(pQuest, rewardIdx, questgiver, true);

                            std::string itemName = pRewardItem->Name1;

                            out << "Quest complete: " << chat->formatQuest(pQuest)
                                << " reward: " << chat->formatItem(pRewardItem);
                        }
                        else
                        {
                            out << "|cffff0000Unable to turn quest in:|r " << chat->formatQuest(pQuest)
                                << " reward: " << chat->formatItem(pRewardItem);
                        }
                    }

                    // else multiple rewards - let master pick
                    else {
                        out << "What reward should I take for " << chat->formatQuest(pQuest) << "? ";
                        for (uint8 i=0; i < pQuest->GetRewChoiceItemsCount(); ++i)
                        {
                            ItemPrototype const * const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[i]);
                            out << chat->formatItem(pRewardItem);
                        }
                    }
                }
            }

            else if (status == QUEST_STATUS_INCOMPLETE) 
            {
                out << "|cffff0000Quest incomplete:|r " << chat->formatQuest(pQuest);
            }

            else if (status == QUEST_STATUS_AVAILABLE || status == QUEST_STATUS_NONE)
            {
                out << "|cff00ff00Quest available:|r " << chat->formatQuest(pQuest);
            }
            
            else if (status == QUEST_STATUS_FAILED) 
            {
                out << "|cffff0000Quest failed:|r " << chat->formatQuest(pQuest);
            }

            if (! out.str().empty())
                ai->TellMaster(out);
        }
    }
}