#pragma once
#include "Value.h"

namespace ai
{
    template<class T>
    class QualifiedStatsValue : public CalculatedValue<T>, public Qualified
	{
	public:
        QualifiedStatsValue(AiManagerRegistry* const ai) : CalculatedValue<T>(ai) {}

    protected:
        Unit* GetTarget()
        {
            return ai->GetAi()->GetAiObjectContext()->GetValue<Unit*>(qualifier.c_str())->Get();
        }
    };

    class HealthValue : public QualifiedStatsValue<uint8>
    {
    public:
        HealthValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

    class IsDeadValue : public QualifiedStatsValue<bool>
    {
    public:
        IsDeadValue(AiManagerRegistry* const ai) : QualifiedStatsValue<bool>(ai) {}

        virtual bool Calculate();
    };

    class RageValue : public QualifiedStatsValue<uint8>
    {
    public:
        RageValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

    class EnergyValue : public QualifiedStatsValue<uint8>
    {
    public:
        EnergyValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

    class ManaValue : public QualifiedStatsValue<uint8>
    {
    public:
        ManaValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

    class HasManaValue : public QualifiedStatsValue<bool>
    {
    public:
        HasManaValue(AiManagerRegistry* const ai) : QualifiedStatsValue<bool>(ai) {}

        virtual bool Calculate();
    };

    class ComboPointsValue : public QualifiedStatsValue<uint8>
    {
    public:
        ComboPointsValue(AiManagerRegistry* const ai) : QualifiedStatsValue(ai) {}

        virtual uint8 Calculate();
    };

    class IsMountedValue : public QualifiedStatsValue<bool>
    {
    public:
        IsMountedValue(AiManagerRegistry* const ai) : QualifiedStatsValue<bool>(ai) {}

        virtual bool Calculate();
    };

}
