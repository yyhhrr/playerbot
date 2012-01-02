#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class EnemyTooCloseTrigger : public Trigger {
    public:
        EnemyTooCloseTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close") {}
        virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, "current target");
            return target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance;
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
        EnemyOutOfMeleeTrigger(PlayerbotAI* ai) : EnemyOutOfRangeTrigger(ai, "enemy out of melee range", sPlayerbotAIConfig.meleeDistance + 1.0f) {}
    };

    class EnemyOutOfSpellRangeTrigger : public EnemyOutOfRangeTrigger
	{
    public:
        EnemyOutOfSpellRangeTrigger(PlayerbotAI* ai) : EnemyOutOfRangeTrigger(ai, "enemy out of spell range", sPlayerbotAIConfig.spellDistance) {}
    };

    class FarFromMasterTrigger : public Trigger {
    public:
        FarFromMasterTrigger(PlayerbotAI* ai, string name = "far from master", float distance = 12.0f) : Trigger(ai, name), distance(distance) {}

        virtual bool IsActive()
        {
            return AI_VALUE2(float, "distance", "master target") > distance;
        }

    private:
        float distance;
    };

    class OutOfReactRangeTrigger : public FarFromMasterTrigger
    {
    public:
        OutOfReactRangeTrigger(PlayerbotAI* ai) : FarFromMasterTrigger(ai, "out of react range", sPlayerbotAIConfig.reactDistance / 2) {}
    };
}
