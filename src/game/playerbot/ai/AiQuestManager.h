#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	enum QuestListFilter {
		QUEST_LIST_FILTER_SUMMARY = 0,
		QUEST_LIST_FILTER_COMPLETED = 1,
		QUEST_LIST_FILTER_INCOMPLETED = 2,
		QUEST_LIST_FILTER_ALL = QUEST_LIST_FILTER_COMPLETED | QUEST_LIST_FILTER_INCOMPLETED
	};

	class AiQuestManager : public AiManagerBase
	{
	public:
		AiQuestManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		void UpdateQuestNeedItems();
		void ListQuests(QuestListFilter filter);
		int ListQuests(bool completed, bool silent);
		void DropQuest(const char* link);
		void QuestLocalization(std::string& questTitle, const uint32 questID);
		map<uint32, uint32> GetQuestItems() { return questNeedItems; }
		void TurnInQuests( WorldObject *questgiver );
		void AcceptQuest( Quest const *qInfo, Player *pGiver );
        void QueryQuestItem(uint32 itemId);

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
        virtual void Query(const string& text);

    private:
        void QueryQuestItem(uint32 itemId, const Quest *questTemplate, QuestStatusData *questStatus);
        void QueryQuest(uint32 id);

	private:
		map<uint32, uint32> questNeedItems;
	};

};