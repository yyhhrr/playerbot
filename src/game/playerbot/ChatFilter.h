#pragma once

using namespace std;

namespace ai
{
    class ChatFilter : public PlayerbotAIAware
    {
    public:
        ChatFilter(PlayerbotAI* ai) : PlayerbotAIAware(ai) {}
        virtual string Filter(string message);
    };

    class StrategyChatFilter : public ChatFilter
    {
    public:
        StrategyChatFilter(PlayerbotAI* ai) : ChatFilter(ai) {}
        virtual string Filter(string message);
    };

    class ClassChatFilter : public ChatFilter
    {
    public:
        ClassChatFilter(PlayerbotAI* ai);
        virtual string Filter(string message);

    private:
        map<string, uint8> classNames;
    };

    class CompositeChatFilter : public ChatFilter
    {
    public:
        CompositeChatFilter(PlayerbotAI* ai);
        virtual ~CompositeChatFilter();
        string Filter(string message);

    private:
        list<ChatFilter*> filters;
    };
};
