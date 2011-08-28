#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class ValueInRangeTrigger : public Trigger {
    public:
        ValueInRangeTrigger(PlayerbotAI* ai, string name, float maxValue, float minValue) : Trigger(ai, name) {
            this->maxValue = maxValue;
            this->minValue = minValue;
        }
    public:
        virtual float GetValue() = 0;
        virtual bool IsActive() {
            float value = GetValue();
            return value < maxValue && value > minValue;
        }

    protected:
        float maxValue, minValue;
    };

	class HealthInRangeTrigger : public ValueInRangeTrigger {
	public:
		HealthInRangeTrigger(PlayerbotAI* ai, string name, float maxValue, float minValue = 0) :
		  ValueInRangeTrigger(ai, name, maxValue, minValue) {}

		  virtual float GetValue();
	};

    class LowHealthTrigger : public HealthInRangeTrigger {
    public:
        LowHealthTrigger(PlayerbotAI* ai, float value = sPlayerbotAIConfig.lowHealth, float minValue = 0) :
            HealthInRangeTrigger(ai, "low health", value, minValue) {}

		virtual string GetTargetName() { return "self target"; }
    };

    class CriticalHealthTrigger : public LowHealthTrigger
    {
    public:
        CriticalHealthTrigger(PlayerbotAI* ai) : LowHealthTrigger(ai, sPlayerbotAIConfig.criticalHealth, 0) {}
    };

    class MediumHealthTrigger : public LowHealthTrigger
    {
    public:
        MediumHealthTrigger(PlayerbotAI* ai) : 
          LowHealthTrigger(ai, sPlayerbotAIConfig.mediumHealth, sPlayerbotAIConfig.lowHealth) {}
    };

    class PartyMemberLowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        PartyMemberLowHealthTrigger(PlayerbotAI* ai, float value = sPlayerbotAIConfig.lowHealth, float minValue = 0) :
            HealthInRangeTrigger(ai, "party member low health", value, minValue) {}

        virtual string GetTargetName() { return "party member to heal"; }
    };

    class PartyMemberCriticalHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberCriticalHealthTrigger(PlayerbotAI* ai) : 
          PartyMemberLowHealthTrigger(ai, sPlayerbotAIConfig.criticalHealth, 0) {}
    };

    class PartyMemberMediumHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberMediumHealthTrigger(PlayerbotAI* ai) : 
          PartyMemberLowHealthTrigger(ai, sPlayerbotAIConfig.mediumHealth,sPlayerbotAIConfig.lowHealth) {}
    };

    class TargetLowHealthTrigger : public HealthInRangeTrigger {
    public:
        TargetLowHealthTrigger(PlayerbotAI* ai, float value, float minValue = 0) :
            HealthInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual string GetTargetName() { return "current target"; }
    };

    class TargetCriticalHealthTrigger : public TargetLowHealthTrigger
    {
    public:
        TargetCriticalHealthTrigger(PlayerbotAI* ai) : TargetLowHealthTrigger(ai, 20) {}
    };

	class PartyMemberDeadTrigger : public Trigger {
	public:
		PartyMemberDeadTrigger(PlayerbotAI* ai) : Trigger(ai, "resurrect", 10) {}
        virtual string GetTargetName() { return "party member to resurrect"; }
		virtual bool IsActive();
	};

    class DeadTrigger : public Trigger {
    public:
        DeadTrigger(PlayerbotAI* ai) : Trigger(ai, "dead", 10) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

}
