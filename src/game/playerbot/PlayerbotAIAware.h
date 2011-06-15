#pragma once

namespace ai
{
    class PlayerbotAIAware 
    {
    public:
        PlayerbotAIAware(PlayerbotAI* const ai) { this->ai = ai; }

    protected:
        PlayerbotAI* ai;
    };
}