#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiMoveManager : public AiManagerBase
	{
	public:
		AiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);

	public:
		virtual void ReleaseSpirit();
		virtual void Resurrect();
		virtual void Revive();
        virtual void Summon();
		virtual void Update();
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
        virtual void HandleMasterIncomingPacket(const WorldPacket& packet);
		virtual void UsePortal();
        void UpdatePosition();

    private:
        void UseMeetingStone(uint64 guid);
        void TeleportToMaster();

	};

};
