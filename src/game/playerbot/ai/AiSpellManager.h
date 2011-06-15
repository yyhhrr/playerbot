#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiSpellManager : public AiManagerBase
	{
	public:
		AiSpellManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);

	public:
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	private:
	};

};
