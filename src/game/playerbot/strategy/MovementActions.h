#pragma once

#include "Action.h"

namespace ai
{
    class FleeAction : public Action {
    public:
        FleeAction(AiManagerRegistry* const ai, float distance = SPELL_DISTANCE) : Action(ai, "flee") {
			this->distance = distance;
		}

        virtual bool Execute(Event event) 
		{
            return ai->GetMoveManager()->Flee(ai->GetTargetManager()->GetCurrentTarget(), distance); 
        }

	private:
		float distance;
    };

	class FollowAction : public Action {
	public:
		FollowAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
		virtual bool Execute(Event event) = NULL;
	};

	class FollowLineAction : public FollowAction {
	public:
		FollowLineAction(AiManagerRegistry* const ai) : FollowAction(ai, "follow line") {}
		virtual bool Execute(Event event);
	};

	class FollowMasterAction : public Action {
	public:
		FollowMasterAction(AiManagerRegistry* const ai) : Action(ai, "follow master") {}
		virtual bool Execute(Event event);
	};

    class StayAction : public Action {
    public:
        StayAction(AiManagerRegistry* const ai) : Action(ai, "stay") {}
        virtual bool Execute(Event event);
    };

	class StayCircleAction : public Action {
	public:
		StayCircleAction(AiManagerRegistry* const ai) : Action(ai, "stay circle") {}
		virtual bool Execute(Event event);
	};

	class StayCombatAction : public Action {
	public:
		StayCombatAction(AiManagerRegistry* const ai) : Action(ai, "stay combat") {}
		virtual bool Execute(Event event);
	};

	class StayLineAction : public Action {
	public:
		StayLineAction(AiManagerRegistry* const ai) : Action(ai, "stay line") {}
		virtual bool Execute(Event event);
	};

    class GoAwayAction : public Action {
    public:
        GoAwayAction(AiManagerRegistry* const ai) : Action(ai, "goaway") {}
        virtual bool Execute(Event event);
    };
}