#pragma once

#include "Action.h"

namespace ai
{
    class FleeAction : public Action {
    public:
        FleeAction(AiManagerRegistry* const ai, float distance = SPELL_DISTANCE) : Action(ai, "flee") {
			this->distance = distance;
		}

        virtual bool ExecuteResult() 
		{
            return ai->GetMoveManager()->Flee(ai->GetTargetManager()->GetCurrentTarget(), distance); 
        }

	private:
		float distance;
    };

	class FollowAction : public Action {
	public:
		FollowAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
		virtual void Execute() = NULL;
	};

	class FollowLineAction : public FollowAction {
	public:
		FollowLineAction(AiManagerRegistry* const ai) : FollowAction(ai, "follow line") {}
		virtual void Execute();
	};

	class FollowMasterAction : public Action {
	public:
		FollowMasterAction(AiManagerRegistry* const ai) : Action(ai, "follow master") {}
		virtual void Execute();
	};

    class StayAction : public Action {
    public:
        StayAction(AiManagerRegistry* const ai) : Action(ai, "stay") {}
        virtual void Execute();
    };

	class StayCircleAction : public Action {
	public:
		StayCircleAction(AiManagerRegistry* const ai) : Action(ai, "stay circle") {}
		virtual void Execute();
	};

	class StayCombatAction : public Action {
	public:
		StayCombatAction(AiManagerRegistry* const ai) : Action(ai, "stay combat") {}
		virtual void Execute();
	};

	class StayLineAction : public Action {
	public:
		StayLineAction(AiManagerRegistry* const ai) : Action(ai, "stay line") {}
		virtual void Execute();
	};

    class GoAwayAction : public Action {
    public:
        GoAwayAction(AiManagerRegistry* const ai) : Action(ai, "goaway") {}
        virtual void Execute();
    };
}