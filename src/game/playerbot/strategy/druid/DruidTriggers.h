#pragma once
#include "../GenericTriggers.h"

namespace ai {
    class MarkOfTheWildOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        MarkOfTheWildOnPartyTrigger(AiManagerRegistry* const ai) : BuffOnPartyTrigger(ai, "mark of the wild") {}
    };

    class MarkOfTheWildTrigger : public BuffTrigger {
    public:
        MarkOfTheWildTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "mark of the wild") {}
    };

    class ThornsTrigger : public BuffTrigger {
    public:
        ThornsTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "thorns") {}
    };

    class RakeTrigger : public DebuffTrigger
    {
    public:
        RakeTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "rake") {}
    };

    class InsectSwarmTrigger : public DebuffTrigger
    {
    public:
        InsectSwarmTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "insect swarm") {}
    };

    class MoonfireTrigger : public DebuffTrigger
    {
    public:
        MoonfireTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "moonfire") {}
    };

    class FaerieFireTrigger : public DebuffTrigger
    {
    public:
        FaerieFireTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "faerie fire") {}
    };

    class FaerieFireFeralTrigger : public DebuffTrigger
    {
    public:
        FaerieFireFeralTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "faerie fire (feral)") {}
    };

    class BashInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        BashInterruptSpellTrigger(AiManagerRegistry* const ai) : InterruptSpellTrigger(ai, "bash") {}
    };

    class TigersFuryTrigger : public BoostTrigger
    {
    public:
        TigersFuryTrigger(AiManagerRegistry* const ai) : BoostTrigger(ai, "tiger's fury") {}
    };

    class EntanglingRootsTrigger : public HasCcTargetTrigger
    {
    public:
        EntanglingRootsTrigger(AiManagerRegistry* const ai) : HasCcTargetTrigger(ai, "entangling roots") {}
    };
    
}
