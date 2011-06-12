#pragma once
#include "StatsValues.h"

namespace ai
{
   
    class AttackerCountValue : public QualifiedStatsValue<uint8>
    {
    public:
        AttackerCountValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

    class MyAttackerCountValue : public QualifiedStatsValue<uint8>
    {
    public:
        MyAttackerCountValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

    class HasAggroValue : public QualifiedStatsValue<bool>
    {
    public:
        HasAggroValue(AiManagerRegistry* const ai) : QualifiedStatsValue<bool>(ai) {}

        virtual bool Calculate();
    };
    
    class BalancePercentValue : public QualifiedStatsValue<uint8>
    {
    public:
        BalancePercentValue(AiManagerRegistry* const ai) : QualifiedStatsValue<uint8>(ai) {}

        virtual uint8 Calculate();
    };

}
