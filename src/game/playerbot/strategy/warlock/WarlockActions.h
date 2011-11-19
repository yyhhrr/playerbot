#pragma once

#include "../actions/GenericActions.h"

namespace ai
{
	class CastDemonSkinAction : public CastBuffSpellAction {
	public:
		CastDemonSkinAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demon skin") {}
	};

	class CastDemonArmorAction : public CastBuffSpellAction 
	{
	public:
		CastDemonArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demon armor") {}
	};

	class CastFelArmorAction : public CastBuffSpellAction
	{
	public:
		CastFelArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fel armor") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

	class CastImmolateAction : public CastDebuffSpellAction 
	{
	public:
		CastImmolateAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "immolate") {}
	};

	class CastDrainSoulAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainSoulAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "drain soul") {}
		virtual bool isUseful() 
		{
			return AI_VALUE2(uint8, "item count", "soul shard") < 2;
		}
	};

	class CastDrainManaAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainManaAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "drain mana") {}
	};

	class CastDrainLifeAction : public CastDebuffSpellAction 
	{
	public:
		CastDrainLifeAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "drain life") {}
	};

	class CastCurseOfAgonyAction : public CastDebuffSpellAction 
	{
	public:
		CastCurseOfAgonyAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "curse of agony") {}
	};

	class CastCurseOfWeaknessAction : public CastDebuffSpellAction 
	{
	public:
		CastCurseOfWeaknessAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "curse of weakness") {}
	};

	class CastCorruptionAction : public CastDebuffSpellAction 
	{
	public:
		CastCorruptionAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "corruption") {}
	};

	
	class CastSummonVoidwalkerAction : public CastBuffSpellAction 
	{
	public:
		CastSummonVoidwalkerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon voidwalker") {}
	};

	class CastSummonImpAction : public CastBuffSpellAction 
	{
	public:
		CastSummonImpAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon imp") {}
	};

	class CastCreateHealthstoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateHealthstoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create healthstone") {}
	};

	class CastCreateFirestoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateFirestoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create firestone") {}
	};

	class CastCreateSpellstoneAction : public CastBuffSpellAction 
	{
	public:
		CastCreateSpellstoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create spellstone") {}
	};

    class CastBanishAction : public CastBuffSpellAction 
    {
    public:
        CastBanishAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "banish") {}
        virtual Value<Unit*>* GetTargetValue();
    };
    
}
