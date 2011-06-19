#pragma once

#include "../Action.h"

namespace ai
{
    class MovementAction : public Action {
    public:
        MovementAction(PlayerbotAI* ai, string name) : Action(ai, name) 
        {
            bot = ai->GetBot();
        }

    protected:
        void MoveNear(uint32 mapId, float x, float y, float z, float distance = 2.0f);
        void MoveTo(uint32 mapId, float x, float y, float z);
        void MoveTo(Unit* target, float distance = 0.0f);
        void MoveNear(WorldObject* target, float distance = 2.0f);
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

    class FleeAction : public MovementAction 
    {
    public:
        FleeAction(PlayerbotAI* ai, float distance = SPELL_DISTANCE) : MovementAction(ai, "flee") 
        {
			this->distance = distance;
		}

        virtual bool Execute(Event event);

	private:
		float distance;
    };


    class GoAwayAction : public MovementAction 
    {
    public:
        GoAwayAction(PlayerbotAI* ai) : MovementAction(ai, "goaway") {}
        virtual bool Execute(Event event);
    };

    class MoveRandomAction : public MovementAction 
    {
    public:
        MoveRandomAction(PlayerbotAI* ai) : MovementAction(ai, "move random") {}
        virtual bool Execute(Event event);
    };
}