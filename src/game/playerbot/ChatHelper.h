#pragma once

using namespace std;

typedef set<uint32> ItemIds;
typedef set<uint32> SpellIds;

namespace ai
{
    class ChatHelper : public PlayerbotAIAware
    {
    public:
        ChatHelper(PlayerbotAI* ai) : PlayerbotAIAware(ai) {}

    public:
        static string formatMoney(uint32 copper);
        static uint32 parseMoney(string& text);
        static ItemIds parseItems(string& text);
        static SpellIds parseSpells(string& text);
        static string formatQuest(Quest const* quest);
        static string formatItem(ItemPrototype const * proto, int count = 0);
        static string formatSpell(SpellEntry const *sInfo);
        static string formatGameobject(GameObject* go);
        static string formatQuestObjective(string name, int available, int required);
        static list<ObjectGuid> parseGameobjects(string& text);

        static ChatMsg parseChat(string& text);
        static string formatChat(ChatMsg chat);
    };
};