#pragma once

class PlayerbotAI;

namespace ai
{
    class AiObjectContext;

    class AiObject : public PlayerbotAIAware
	{
	public:
        AiObject(PlayerbotAI* ai);

    protected:
        Player* bot;
        Player* master;
        AiObjectContext* context;
	};
}
