#include "../../pchdef.h"
#include "../playerbot.h"
#include "../strategy/LogLevelAction.h"

using namespace ai;
using namespace std;

void AiSocialManager::TellMaster(LogLevel level, const char* text)
{
    LogLevel logLevel = *ai->GetAiObjectContext()->GetValue<LogLevel>("log level");

	if (logLevel < level)
		return;

	ostringstream out;
    out << LogLevelAction::logLevel2string(level) << ": " << text;
	TellMaster(out.str().c_str());
}

void AiSocialManager::TellMaster(const char* text)
{
	WorldPacket data(SMSG_MESSAGECHAT, 1024);
	bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, text, LANG_UNIVERSAL);
	ai->GetMaster()->GetSession()->SendPacket(&data);
	bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
}

void AiSocialManager::HandleCommand(const string& text, Player& fromPlayer)
{
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