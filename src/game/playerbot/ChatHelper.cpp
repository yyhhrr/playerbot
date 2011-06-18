#include "../pchdef.h"
#include "playerbot.h"
#include "ChatHelper.h"

using namespace ai;
using namespace std;

uint32 ChatHelper::parseMoney(string& text)
{
    // if user specified money in ##g##s##c format
    string acum = "";
    uint32 copper = 0;
    for (uint8 i = 0; i < text.length(); i++)
    {
        if (text[i] == 'g')
        {
            copper += (atol(acum.c_str()) * 100 * 100);
            acum = "";
        }
        else if (text[i] == 'c')
        {
            copper += atol(acum.c_str());
            acum = "";
        }
        else if (text[i] == 's')
        {
            copper += (atol(acum.c_str()) * 100);
            acum = "";
        }
        else if (text[i] == ' ')
            break;
        else if (text[i] >= 48 && text[i] <= 57)
            acum += text[i];
        else
        {
            copper = 0;
            break;
        }
    }
    return copper;
}

ItemIds ChatHelper::parseItems(string& text)
{
    ItemIds itemIds;

    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hitem:", pos);
        if (i == -1)
            break;
        pos = i + 6;
        int endPos = text.find(':', pos);
        if (endPos == -1)
            break;
        string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos;
        if (id)
            itemIds.insert(id);
    }

    return itemIds;
}

string ChatHelper::formatQuest(Quest const* quest)
{
    ostringstream out;
    out << "|cFFFFFF00|Hquest:" << quest->GetQuestId() << ':' << quest->GetQuestLevel() << "|h[" << quest->GetTitle() << "]|h|r";
    return out.str();
}
