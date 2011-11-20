#include "../pchdef.h"
#include "playerbot.h"
#include "ChatFilter.h"

using namespace ai;
using namespace std;

string ChatFilter::Filter(string message)
{
    if (message.find("@") == string::npos)
        return message;

    return message.substr(message.find(" ") + 1);
}

string StrategyChatFilter::Filter(string message)
{
    Player* bot = ai->GetBot();

    bool tank = message.find("@tank") == 0;
    if (tank && !ai->IsTank(bot))
        return "";

    bool dps = message.find("@dps") == 0 || message.find("@heal") == 0;
    if (dps && ai->IsTank(bot))
        return "";

	if (tank || dps)
		return ChatFilter::Filter(message);

	return message;
}

ClassChatFilter::ClassChatFilter(PlayerbotAI* ai) : ChatFilter(ai)
{
    classNames["@death_knight"] = CLASS_DEATH_KNIGHT;
    classNames["@druid"] = CLASS_DRUID;
    classNames["@hunter"] = CLASS_HUNTER;
    classNames["@mage"] = CLASS_MAGE;
    classNames["@paladin"] = CLASS_PALADIN;
    classNames["@priest"] = CLASS_PRIEST;
    classNames["@rogue"] = CLASS_ROGUE;
    classNames["@shaman"] = CLASS_SHAMAN;
    classNames["@warlock"] = CLASS_WARLOCK;
    classNames["@warrior"] = CLASS_WARRIOR;
}

string ClassChatFilter::Filter(string message)
{
    Player* bot = ai->GetBot();

	bool found = false;
    for (map<string, uint8>::iterator i = classNames.begin(); i != classNames.end(); i++)
    {
		bool isClass = message.find(i->first) == 0;
        if (isClass && bot->getClass() != i->second)
            return "";

		found |= isClass;
    }

	if (found)
		return ChatFilter::Filter(message);

	return message;
}

CompositeChatFilter::CompositeChatFilter(PlayerbotAI* ai) : ChatFilter(ai)
{
    filters.push_back(new StrategyChatFilter(ai));
    filters.push_back(new ClassChatFilter(ai));
}

CompositeChatFilter::~CompositeChatFilter()
{
    for (list<ChatFilter*>::iterator i = filters.begin(); i != filters.end(); i++)
        delete (*i);
}

string CompositeChatFilter::Filter(string message)
{
    for (list<ChatFilter*>::iterator i = filters.begin(); i != filters.end(); i++)
    {
        message = (*i)->Filter(message);
        if (message.empty())
            break;
    }

    return message;
}

