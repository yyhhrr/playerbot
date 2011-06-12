#pragma once

#include "../GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(PowerWordFortitudeOnPartyTrigger, "power word: fortitude", "power word: fortitude on party")
    BUFF_TRIGGER(PowerWordFortitudeTrigger, "power word: fortitude", "power word: fortitude")

    BUFF_ON_PARTY_TRIGGER(DivineSpiritOnPartyTrigger, "divine spirit", "divine spirit on party")
    BUFF_TRIGGER(DivineSpiritTrigger, "divine spirit", "divine spirit")
    BUFF_TRIGGER(InnerFireTrigger, "inner fire", "inner fire")

    DEBUFF_TRIGGER(PowerWordPainTrigger, "shadow word: pain", "shadow word: pain")
    DEBUFF_TRIGGER(DevouringPlagueTrigger, "devouring plague", "devouring plague")

    class DispelMagicTrigger : public NeedCureTrigger 
    {
    public:
        DispelMagicTrigger(AiManagerRegistry* const ai) : NeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class DispelMagicPartyMemberTrigger : public PartyMemberNeedCureTrigger 
    {
    public:
        DispelMagicPartyMemberTrigger(AiManagerRegistry* const ai) : PartyMemberNeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class CureDiseaseTrigger : public NeedCureTrigger 
    {
    public:
        CureDiseaseTrigger(AiManagerRegistry* const ai) : NeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    class PartyMemberCureDiseaseTrigger : public PartyMemberNeedCureTrigger 
    {
    public:
        PartyMemberCureDiseaseTrigger(AiManagerRegistry* const ai) : PartyMemberNeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };
}