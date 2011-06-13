#pragma once

#include "Action.h"
#include "MovementActions.h"

namespace ai
{
	class FollowAction : public MovementAction {
	public:
		FollowAction(AiManagerRegistry* const ai, const char* name) : MovementAction(ai, name) {}
	};

	class FollowLineAction : public FollowAction {
	public:
		FollowLineAction(AiManagerRegistry* const ai) : FollowAction(ai, "follow line") {}
		virtual bool Execute(Event event);
	};

	class FollowMasterAction : public MovementAction {
	public:
		FollowMasterAction(AiManagerRegistry* const ai) : MovementAction(ai, "follow master") {}
		virtual bool Execute(Event event);
	};
}