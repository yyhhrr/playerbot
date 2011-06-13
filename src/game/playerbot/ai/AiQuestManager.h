#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiQuestManager : public AiManagerBase
	{
	public:
		AiQuestManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		void QuestLocalization(std::string& questTitle, const uint32 questID);
        void QueryQuestItem(uint32 itemId);

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
		virtual void HandleMasterIncomingPacket(const WorldPacket& packet);
        virtual void Query(const string& text);

    private:
        void QueryQuestItem(uint32 itemId, const Quest *questTemplate, QuestStatusData *questStatus);
        void QueryQuest(uint32 id);
	};

};