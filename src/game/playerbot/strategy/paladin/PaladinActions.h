#pragma once
#include "../actions/GenericActions.h"

namespace ai
{
    class CastJudgementOfLightAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfLightAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "judgement of light") {}
    };

    class CastJudgementOfWisdomAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfWisdomAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "judgement of wisdom") {}
    };

    class CastJudgementOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfJusticeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "judgement of justice") {}
    };

	class CastRighteousFuryAction : public CastBuffSpellAction {
	public:
		CastRighteousFuryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "righteous fury") {}
	};

	class CastDevotionAuraAction : public CastBuffSpellAction {
	public:
		CastDevotionAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "devotion aura") {}
	};

	class CastRetributionAuraAction : public CastBuffSpellAction {
	public:
		CastRetributionAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "retribution aura") {}
	};

	class CastConcentrationAuraAction : public CastBuffSpellAction {
	public:
		CastConcentrationAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "concentration aura") {}
	};

	class CastDivineStormAction : public CastBuffSpellAction {
	public:
		CastDivineStormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine storm") {}
	};

	class CastCrusaderStrikeAction : public CastMeleeSpellAction {
	public:
		CastCrusaderStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "crusader strike") {}
	};

	class CastShadowResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastShadowResistanceAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shadow resistance aura") {}
	};

	class CastFrostResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastFrostResistanceAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frost resistance aura") {}
	};

	class CastFireResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastFireResistanceAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fire resistance aura") {}
	};

	class CastCrusaderAuraAction : public CastBuffSpellAction {
	public:
		CastCrusaderAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "crusader aura") {}
	};

	class CastSealOfRighteousnessAction : public CastBuffSpellAction {
	public:
		CastSealOfRighteousnessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "seal of righteousness") {}
	};

	class CastSealOfJusticeAction : public CastBuffSpellAction {
	public:
		CastSealOfJusticeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "seal of justice") {}
	};


	class CastSealOfLightAction : public CastBuffSpellAction {
	public:
		CastSealOfLightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "seal of light") {}
	};

	class CastSealOfWisdomAction : public CastBuffSpellAction {
	public:
		CastSealOfWisdomAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "seal of wisdom") {}
	};

	class CastSealOfCommandAction : public CastBuffSpellAction {
	public:
		CastSealOfCommandAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "seal of command") {}
	};


	class CastBlessingOfMightAction : public CastBuffSpellAction {
	public:
		CastBlessingOfMightAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of might") {}
	};

	class CastBlessingOfMightOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfMightOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of might") {}
        virtual const char* getName() { return "blessing of might on party";}
	};

	class CastBlessingOfWisdomAction : public CastBuffSpellAction {
	public:
		CastBlessingOfWisdomAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of wisdom") {}
	};

	class CastBlessingOfWisdomOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfWisdomOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of wisdom") {}
        virtual const char* getName() { return "blessing of wisdom on party";}
	};

	class CastBlessingOfKingsAction : public CastBuffSpellAction {
	public:
		CastBlessingOfKingsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of kings") {}
	};

	class CastBlessingOfKingsOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfKingsOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of kings") {}
        virtual const char* getName() { return "blessing of kings on party";}
	};

	class CastBlessingOfSanctuaryAction : public CastBuffSpellAction {
	public:
		CastBlessingOfSanctuaryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blessing of sanctuary") {}
	};

	class CastBlessingOfSanctuaryOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfSanctuaryOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "blessing of sanctuary") {}
        virtual const char* getName() { return "blessing of sanctuary on party";}
	};

    class CastHolyLightAction : public CastHealingSpellAction {
    public:
        CastHolyLightAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "holy light") {}
    };

    class CastHolyLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHolyLightOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "holy light") {}

        virtual const char* getName() { return "holy light on party"; }
    };

    class CastFlashOfLightAction : public CastHealingSpellAction {
    public:
        CastFlashOfLightAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "flash of light") {}
    };

    class CastFlashOfLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashOfLightOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "flash of light") {}

        virtual const char* getName() { return "flash of light on party"; }
    };

    class CastLayOnHandsAction : public CastHealingSpellAction {
    public:
        CastLayOnHandsAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lay on hands") {}
    };

    class CastLayOnHandsOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLayOnHandsOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "lay on hands") {}

        virtual const char* getName() { return "lay on hands on party"; }
    };

	class CastDivineProtectionAction : public CastBuffSpellAction {
	public:
		CastDivineProtectionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine protection") {}
	};

    class CastDivineProtectionOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastDivineProtectionOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "divine protection") {}

        virtual const char* getName() { return "divine protection on party"; }
    };

	class CastDivineShieldAction: public CastBuffSpellAction {
	public:
		CastDivineShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine shield") {}
	};

    BEGIN_SPELL_ACTION(CastConsecrationAction, "consecration")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyWrathAction, "holy wrath")
    END_SPELL_ACTION()

    class CastHammerOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastHammerOfJusticeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hammer of justice") {}
    };

	class CastHammerOfWrathAction : public CastMeleeSpellAction {
	public:
		CastHammerOfWrathAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hammer of wrath") {}
	};

	class CastHammerOfTheRighteousAction : public CastMeleeSpellAction {
	public:
		CastHammerOfTheRighteousAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hammer of the righteous") {}
	};

	class CastPurifyAction : public CastCureSpellAction {
	public:
		CastPurifyAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "purify") {}
	};

    class CastPurifyPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyPoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "purify", DISPEL_POISON) {}

        virtual const char* getName() { return "purify poison on party"; }
    };

	class CastPurifyDiseaseOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastPurifyDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "purify", DISPEL_DISEASE) {}

		virtual const char* getName() { return "purify disease on party"; }
	};

	class CastHandOfReckoningAction : public CastDebuffSpellAction {
	public:
		CastHandOfReckoningAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "hand of reckoning") {}
	};

	class CastCleanseAction : public CastCureSpellAction {
	public:
		CastCleanseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cleanse") {}
	};

    class CastCleansePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleansePoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_POISON) {}

        virtual const char* getName() { return "cleanse poison on party"; }
    };

	class CastCleanseDiseaseOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastCleanseDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_DISEASE) {}

		virtual const char* getName() { return "cleanse disease on party"; }
	};

	class CastCleanseMagicOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastCleanseMagicOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_MAGIC) {}

		virtual const char* getName() { return "cleanse magic on party"; }
	};

    BEGIN_SPELL_ACTION(CastAvengersShieldAction, "avenger's shield")
    END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastExorcismAction, "exorcism")
	END_SPELL_ACTION()

	class CastHolyShieldAction : public CastBuffSpellAction {
	public:
		CastHolyShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "holy shield") {}
	};

	class CastRedemptionAction : public ResurrectPartyMemberAction
	{
	public:
		CastRedemptionAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "redemption") {}
	};
}
