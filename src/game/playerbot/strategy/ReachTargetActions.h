#pragma once

#include "Action.h"
#include "MovementActions.h"

namespace ai
{
    class ReachTargetAction : public MovementAction {
    public:
        ReachTargetAction(AiManagerRegistry* const ai, const char* name, float distance) : MovementAction(ai, name) 
		{
            this->distance = distance;
        }
        virtual bool Execute(Event event) 
		{
			MoveTo(AI_VALUE(Unit*, "current target"), distance);
            return true;
        }
        virtual bool isUseful() 
		{
            return AI_VALUE2(float, "distance", "current target") > distance;
        }
        virtual const char* GetTargetName() { return "current target"; }

    protected:
        float distance;
    };

    class CastReachTargetSpellAction : public CastSpellAction {
    public:
        CastReachTargetSpellAction(AiManagerRegistry* const ai, const char* spell, float distance) : CastSpellAction(ai, spell) 
		{
            this->distance = distance;
        }
		virtual bool isUseful() 
		{
			return AI_VALUE2(float, "distance", "current target") > distance;
		}

    protected:
        float distance;
    };

    class ReachMeleeAction : public ReachTargetAction 
	{
    public:
        ReachMeleeAction(AiManagerRegistry* const ai) : ReachTargetAction(ai, "reach melee", 1.5f) {}
    };

    class ReachSpellAction : public ReachTargetAction 
	{
    public:
        ReachSpellAction(AiManagerRegistry* const ai, float distance = SPELL_DISTANCE) : ReachTargetAction(ai, "reach spell", distance) {}
    };
}