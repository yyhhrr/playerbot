#pragma once
#include "../Trigger.h"

namespace ai
{
    class EnemyTooCloseTrigger : public Trigger {
    public:
        EnemyTooCloseTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close") {}
        virtual bool IsActive() 
		{
			Unit* target = AI_VALUE(Unit*, "current target");
            return target && AI_VALUE2(float, "distance", "current target") <= ATTACK_DISTANCE;
        }
    };

    class EnemyOutOfRangeTrigger : public Trigger {
    public:
        EnemyOutOfRangeTrigger(PlayerbotAI* ai, string name, float distance) : Trigger(ai, name) 
		{
            this->distance = distance;
        }
        virtual bool IsActive() 
		{
			Unit* target = AI_VALUE(Unit*, "current target");
			return target && AI_VALUE2(float, "distance", "current target") > distance;
        }

    protected:
        float distance;
    };

    class EnemyOutOfMeleeTrigger : public EnemyOutOfRangeTrigger 
	{
    public:
        EnemyOutOfMeleeTrigger(PlayerbotAI* ai) : EnemyOutOfRangeTrigger(ai, "enemy out of melee range", ATTACK_DISTANCE) {}
    };

    class EnemyOutOfSpellRangeTrigger : public EnemyOutOfRangeTrigger 
	{
    public:
        EnemyOutOfSpellRangeTrigger(PlayerbotAI* ai) : EnemyOutOfRangeTrigger(ai, "enemy out of spell range", SPELL_DISTANCE) {}
    };

    class FarFromMasterTrigger : public Trigger {
    public:
        FarFromMasterTrigger(PlayerbotAI* ai) : Trigger(ai, "far from master") {}

        virtual bool IsActive() 
        {
            return AI_VALUE2(float, "distance", "master target") > 12.0f;
        }
    };
}