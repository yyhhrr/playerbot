#pragma once

#include "Action.h"

namespace ai
{
    class MovementAction : public Action {
    public:
        MovementAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) 
        {
            bot = ai->GetAi()->GetBot();
        }

    protected:
        void MoveTo(uint32 mapId, float x, float y, float z);
        void MoveTo(Unit* target, float distance = 0.0f);
        void MoveTo(WorldObject* target);
        float GetFollowAngle();
        void Follow(Unit* target, float distance = 2.0f);
        void Follow(Unit* target, float distance, float angle);
        void WaitForReach(float distance);
        bool IsMovingAllowed(Unit* target);
        bool IsMovingAllowed(uint32 mapId, float x, float y, float z);
        bool IsMovingAllowed();
        bool Flee(Unit *target);

    protected:
        Player* bot;
    };

    class FleeAction : public MovementAction {
    public:
        FleeAction(AiManagerRegistry* const ai, float distance = SPELL_DISTANCE) : MovementAction(ai, "flee") {
			this->distance = distance;
		}

        virtual bool Execute(Event event);

	private:
		float distance;
    };


    class GoAwayAction : public MovementAction {
    public:
        GoAwayAction(AiManagerRegistry* const ai) : MovementAction(ai, "goaway") {}
        virtual bool Execute(Event event);
    };
}