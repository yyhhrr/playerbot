#pragma once

namespace ai
{
	class ReviveFromCorpseAction : public Action {
	public:
		ReviveFromCorpseAction(PlayerbotAI* ai) : Action(ai, "revive") {}

    public:
        virtual bool Execute(Event event);
    };

}