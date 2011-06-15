#include "../../pchdef.h"
#include "../playerbot.h"
#include "../../Chat.h"

using namespace ai;
using namespace std;

uint32 PlayerbotChatHandler::extractQuestId(const char *str)
{
	char* source = (char*)str;
    char* cId = ExtractKeyFromLink(&source,"Hquest");
    return cId ? atol(cId) : 0;
}

AiManagerBase::AiManagerBase(PlayerbotAI* ai, AiManagerRegistry* aiRegistry)
{
	this->ai = ai;
	this->bot = ai->GetBot();
	this->aiRegistry = aiRegistry;
}

