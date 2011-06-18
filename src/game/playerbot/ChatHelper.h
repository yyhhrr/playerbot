#pragma once

using namespace std;

typedef set<uint32> ItemIds;

namespace ai
{
    class ChatHelper : public PlayerbotAIAware
    {
    public:
        ChatHelper(PlayerbotAI* ai) : PlayerbotAIAware(ai) {}

    public:
        static uint32 parseMoney(string& text);
        static ItemIds parseItems(string& text);
        static string formatQuest(Quest const* quest);
    };
};