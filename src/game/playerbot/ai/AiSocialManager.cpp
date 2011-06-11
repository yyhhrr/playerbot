#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

void AiSocialManager::TellMaster(LogLevel level, const char* text)
{
	if (logLevel < level)
		return;

	ostringstream out;
	out << GetLogLevel(level) << ": " << text;
	TellMaster(out.str().c_str());
}

void AiSocialManager::TellMaster(const char* text)
{
	WorldPacket data(SMSG_MESSAGECHAT, 1024);
	bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, text, LANG_UNIVERSAL);
	ai->GetMaster()->GetSession()->SendPacket(&data);
	bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
}

string AiSocialManager::GetLogLevel(LogLevel level) 
{
	switch (level) 
	{
	case LOG_LVL_BASIC:
		return "basic";
	case LOG_LVL_MINIMAL:
		return "minimal";
	case LOG_LVL_DETAIL:
		return "detail";
	default:
		return "debug";
	}
}

void AiSocialManager::SetLogLevel(string level) 
{
	if (level == "debug")
		logLevel = LOG_LVL_DEBUG;
	else if (level == "minimal")
		logLevel = LOG_LVL_MINIMAL;
	else if (level == "detail")
		logLevel = LOG_LVL_DETAIL;
	else 
		logLevel = LOG_LVL_BASIC;
}

void AiSocialManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text.size() > 4 && text.substr(0, 4) == "log ")
	{
		string level = text.substr(text.find(" ") + 1);
		if (level == "?")
		{
			ostringstream out;
			out << "Log level: " << GetLogLevel(logLevel);
			TellMaster(out.str().c_str());
		}
		
		SetLogLevel(level);
	}
}

void AiSocialManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
}

void AiSocialManager::ListUnits(const char* title, list<Unit*> units)
{
	TellMaster(title);
	
	for (list<Unit*>::iterator i = units.begin(); i != units.end(); i++)
		TellMaster((*i)->GetName());

}
void AiSocialManager::ListGameObjects(const char* title, list<GameObject*> gos)
{
	TellMaster(title);

	for (list<GameObject*>::iterator i = gos.begin(); i != gos.end(); i++)
		TellMaster((*i)->GetGOInfo()->name);
}

void AiSocialManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
}