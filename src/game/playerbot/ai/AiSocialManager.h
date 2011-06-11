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
			logLevel = LOG_LVL_BASIC;
		}

	public:
		virtual void TellMaster(const char* text);
		virtual void TellMaster(LogLevel level, const char* text);
		void ListUnits(const char* title, list<Unit*> units);
		void ListGameObjects(const char* title, list<GameObject*> gos);
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
		virtual void HandleMasterIncomingPacket(const WorldPacket& packet);

	private:
		string GetLogLevel(LogLevel level);
		void SetLogLevel(string level);

	private:
		LogLevel logLevel;
	};

};