#include "../pchdef.h"
#include "playerbot.h"
#include "ChatHelper.h"

using namespace ai;
using namespace std;

string ChatHelper::formatMoney(uint32 copper)
{
    ostringstream out;
    uint32 gold = uint32(copper / 10000);
    copper -= (gold * 10000);
    uint32 silver = uint32(copper / 100);
    copper -= (silver * 100);
    out << " ";
    if (gold > 0)
        out << gold <<  "|TInterface\\AddOns\\AtlasLoot\\Images\\gold:0|t ";
    if (silver > 0)
        out << silver <<  "|TInterface\\AddOns\\AtlasLoot\\Images\\silver:0|t ";
    out << copper <<  "|TInterface\\AddOns\\AtlasLoot\\Images\\bronze:0|t";

    return out.str();
}

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

string ChatHelper::formatGameobject(GameObject* go)
{
    ostringstream out;
    out << "|cFFFFFF00|Hfound:" << go->GetObjectGuid().GetRawValue() << ":" << go->GetEntry() << ":" <<  "|h[" << go->GetGOInfo()->name << "]|h|r";
    return out.str();
}

string ChatHelper::formatSpell(SpellEntry const *sInfo)
{
    ostringstream out;
    out << "|cffffffff|Hspell:" << sInfo->Id << "|h[" << sInfo->SpellName[LOCALE_enUS] << "]|h|r";
    return out.str();
}

string ChatHelper::formatItem(ItemPrototype const * proto, int count)
{
    char color[32];
    sprintf(color, "%x", ItemQualityColors[proto->Quality]);

    ostringstream out;
    out << " |c" << color << "|Hitem:" << proto->ItemId
        << ":0:0:0:0:0:0:0" << "|h[" << proto->Name1
        << "]|h|r";
    
    if (count > 1)
        out << "x" << count;

    return out.str();
}

ChatMsg ChatHelper::parseChat(string& text)
{
    if (text == "party" || text == "p")
        return CHAT_MSG_PARTY;
    if (text == "guild" || text == "g")
        return CHAT_MSG_GUILD;
    if (text == "raid" || text == "r")
        return CHAT_MSG_RAID;
    if (text == "whisper" || text == "w")
        return CHAT_MSG_WHISPER;
    
    return CHAT_MSG_SYSTEM;
}

string ChatHelper::formatChat(ChatMsg chat)
{
    switch (chat)
    {
    case CHAT_MSG_GUILD:
        return "guild";
    case CHAT_MSG_PARTY:
        return "party";
    case CHAT_MSG_WHISPER:
        return "whisper";
    case CHAT_MSG_RAID:
        return "raid";
    }

    return "unknown";
}


SpellIds ChatHelper::parseSpells(string& text)
{
    SpellIds spells;

    //   Link format
    //   |cffffffff|Hspell:" << spellId << ":" << "|h[" << pSpellInfo->SpellName[loc] << "]|h|r";
    //   cast |cff71d5ff|Hspell:686|h[Shadow Bolt]|h|r";
    //   012345678901234567890123456
    //        base = 16 >|  +7 >|

    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hspell:", pos);
        if (i == -1)
            break;

        // DEBUG_LOG("[PlayerbotAI]: extractSpellIdList - first pos %u i %u",pos,i);
        pos = i + 7;     // start of window in text 16 + 7 = 23
        int endPos = text.find('|', pos);
        if (endPos == -1)
            break;

        // DEBUG_LOG("[PlayerbotAI]: extractSpellIdList - second endpos : %u pos : %u",endPos,pos);
        std::string idC = text.substr(pos, endPos - pos);     // 26 - 23
        uint32 spellId = atol(idC.c_str());
        pos = endPos;     // end

        if (spellId)
            spells.insert(spellId);
    }
    
    return spells;
}