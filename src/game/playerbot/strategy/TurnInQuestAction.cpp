#include "../../pchdef.h"
#include "../playerbot.h"
#include "TurnInQuestAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool TurnInQuestAction::Execute(Event event)
{
    Player *master = ai->GetAi()->GetMaster();

    ObjectGuid guid = event.getObject();
    if (!guid)
        return false;

    GameObject *obj = ai->GetAi()->GetGameObject(guid);
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
    Player* bot = ai->GetAi()->GetBot();
    Player *master = ai->GetAi()->GetMaster();

    uint64 giverGUID = questgiver->GetGUID();

    if( !bot->IsInMap( questgiver ) )
        ai->GetAi()->TellMaster("hey you are turning in quests without me!");
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
                            out << "Quest complete: |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
                        }
                        else
                        {
                            out << "|cffff0000Unable to turn quest in:|r |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
                        }
                    }

                    // auto reward quest if one item as reward
                    else if (pQuest->GetRewChoiceItemsCount() == 1)
                    {
                        int rewardIdx = 0;
                        ItemPrototype const *pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
                        std::string itemName = pRewardItem->Name1;
                        ai->GetInventoryManager()->ItemLocalization(itemName, pRewardItem->ItemId);
                        if (bot->CanRewardQuest(pQuest, rewardIdx, false))
                        {
                            bot->RewardQuest(pQuest, rewardIdx, questgiver, true);

                            std::string itemName = pRewardItem->Name1;
                            ai->GetInventoryManager()->ItemLocalization(itemName, pRewardItem->ItemId);

                            out << "Quest complete: "
                                << " |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() 
                                << "|h[" << questTitle << "]|h|r reward: |cffffffff|Hitem:" 
                                << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
                        }
                        else
                        {
                            out << "|cffff0000Unable to turn quest in:|r "
                                << "|cff808080|Hquest:" << questID << ':' 
                                << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r"
                                << " reward: |cffffffff|Hitem:" 
                                << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
                        }
                    }

                    // else multiple rewards - let master pick
                    else {
                        out << "What reward should I take for |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() 
                            << "|h[" << questTitle << "]|h|r? ";
                        for (uint8 i=0; i < pQuest->GetRewChoiceItemsCount(); ++i)
                        {
                            ItemPrototype const * const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[i]);
                            std::string itemName = pRewardItem->Name1;
                            ai->GetInventoryManager()->ItemLocalization(itemName, pRewardItem->ItemId);
                            out << "|cffffffff|Hitem:" << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
                        }
                    }
                }
            }

            else if (status == QUEST_STATUS_INCOMPLETE) {
                out << "|cffff0000Quest incomplete:|r " 
                    << " |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
            }

            else if (status == QUEST_STATUS_AVAILABLE){
                out << "|cff00ff00Quest available:|r " 
                    << " |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
            }

            if (! out.str().empty())
                ai->GetAi()->TellMaster(out.str().c_str());
        }
    }
}