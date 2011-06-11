#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiSocialManager : public AiManagerBase
	{
	public:
		AiSocialManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual void TellMaster(const char* text);
		virtual void TellMaster(LogLevel level, const char* text);
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
		virtual void HandleMasterIncomingPacket(const WorldPacket& packet);
	};

};