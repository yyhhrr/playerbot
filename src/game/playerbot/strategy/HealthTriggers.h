#pragma once
#include "Trigger.h"

namespace ai
{
    class ValueInRangeTrigger : public Trigger {
    public:
        ValueInRangeTrigger(AiManagerRegistry* const ai, const char* name, float maxValue, float minValue) : Trigger(ai, name) {
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
		HealthInRangeTrigger(AiManagerRegistry* const ai, const char* name, float maxValue, float minValue = 0) :
		  ValueInRangeTrigger(ai, name, maxValue, minValue) {}

		  virtual Unit* GetTarget() = 0;
		  virtual float GetValue();
	};
        
    class LowHealthTrigger : public HealthInRangeTrigger {
    public:
        LowHealthTrigger(AiManagerRegistry* const ai, float value = LOW_HEALTH_PERCENT, float minValue = 0) :
            HealthInRangeTrigger(ai, "low health", value, minValue) {}

		virtual Unit* GetTarget();
    };

    class CriticalHealthTrigger : public LowHealthTrigger 
    {
    public:
        CriticalHealthTrigger(AiManagerRegistry* const ai) : LowHealthTrigger(ai, 25) {}
    };

    class MediumHealthTrigger : public LowHealthTrigger 
    {
    public:
        MediumHealthTrigger(AiManagerRegistry* const ai) : LowHealthTrigger(ai, 60, 40) {}
    };

    class PartyMemberLowHealthTrigger : public HealthInRangeTrigger {
    public:
        PartyMemberLowHealthTrigger(AiManagerRegistry* const ai, float value = LOW_HEALTH_PERCENT, float minValue = 0) :
            HealthInRangeTrigger(ai, "party member low health", value, minValue) {}
        virtual Unit* GetTarget();
    };

    class PartyMemberCriticalHealthTrigger : public PartyMemberLowHealthTrigger 
    {
    public:
        PartyMemberCriticalHealthTrigger(AiManagerRegistry* const ai) : PartyMemberLowHealthTrigger(ai, 25) {}
    };

    class PartyMemberMediumHealthTrigger : public PartyMemberLowHealthTrigger 
    {
    public:
        PartyMemberMediumHealthTrigger(AiManagerRegistry* const ai) : PartyMemberLowHealthTrigger(ai, 60, 40) {}
    };

    class TargetLowHealthTrigger : public HealthInRangeTrigger {
    public:
        TargetLowHealthTrigger(AiManagerRegistry* const ai, float value, float minValue = 0) : 
            HealthInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual Unit* GetTarget();
    };

    class TargetCriticalHealthTrigger : public TargetLowHealthTrigger 
    {
    public:
        TargetCriticalHealthTrigger(AiManagerRegistry* const ai) : TargetLowHealthTrigger(ai, 20) {}
    };

	class PartyMemberDeadTrigger : public Trigger {
	public:
		PartyMemberDeadTrigger(AiManagerRegistry* const ai) : Trigger(ai, "resurrect", 10) {}
		virtual bool IsActive();
	};

}
