#pragma once

#include "../actions/GenericActions.h"
#include "DruidShapeshiftActions.h"
#include "DruidBearActions.h"
#include "DruidCatActions.h"

namespace ai
{
	class CastFaerieFireAction : public CastSpellAction
	{
	public:
		CastFaerieFireAction(PlayerbotAI* ai) : CastSpellAction(ai, "faerie fire") {}
	};

    class CastFaerieFireFeralAction : public CastSpellAction
    {
    public:
        CastFaerieFireFeralAction(PlayerbotAI* ai) : CastSpellAction(ai, "faerie fire (feral)") {}
    };

	class CastRejuvenationAction : public CastHealingSpellAction {
	public:
		CastRejuvenationAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "rejuvenation") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastHealingSpellAction::getPrerequisites());
		}

	};

	class CastRegrowthAction : public CastHealingSpellAction {
	public:
		CastRegrowthAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "regrowth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastHealingSpellAction::getPrerequisites());
		}

	};

    class CastHealingTouchAction : public CastHealingSpellAction {
    public:
        CastHealingTouchAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "healing touch") {}

        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastHealingSpellAction::getPrerequisites());
        }

    };

    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "rejuvenation") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), HealPartyMemberAction::getPrerequisites());
		}
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "regrowth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), HealPartyMemberAction::getPrerequisites());
		}
    };

    class CastHealingTouchOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingTouchOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "healing touch") {}

        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), HealPartyMemberAction::getPrerequisites());
        }
    };

	class CastReviveAction : public ResurrectPartyMemberAction
	{
	public:
		CastReviveAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "revive") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastRebirthAction : public ResurrectPartyMemberAction
	{
	public:
		CastRebirthAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "rebirth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastMarkOfTheWildAction : public CastBuffSpellAction {
	public:
		CastMarkOfTheWildAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "mark of the wild") {}
	};

	class CastMarkOfTheWildOnPartyAction : public BuffOnPartyAction {
	public:
		CastMarkOfTheWildOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "mark of the wild") {}
	};

	class CastSurvivalInstinctsAction : public CastBuffSpellAction {
	public:
		CastSurvivalInstinctsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "survival instincts") {}
	};

	class CastThornsAction : public CastBuffSpellAction {
	public:
		CastThornsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "thorns") {}
	};

	class CastWrathAction : public CastSpellAction
	{
	public:
		CastWrathAction(PlayerbotAI* ai) : CastSpellAction(ai, "wrath") {}
	};

	class CastStarfallAction : public CastSpellAction
	{
	public:
		CastStarfallAction(PlayerbotAI* ai) : CastSpellAction(ai, "starfall") {}
	};

	class CastMoonfireAction : public CastDebuffSpellAction
	{
	public:
		CastMoonfireAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "moonfire") {}
	};

	class CastInsectSwarmAction : public CastDebuffSpellAction
	{
	public:
		CastInsectSwarmAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "insect swarm") {}
	};

	class CastStarfireAction : public CastSpellAction
	{
	public:
		CastStarfireAction(PlayerbotAI* ai) : CastSpellAction(ai, "starfire") {}
	};

	class CastEntanglingRootsAction : public CastDebuffSpellAction
	{
	public:
		CastEntanglingRootsAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "entangling roots") {}
	};

    class CastEntanglingRootsCcAction : public CastDebuffSpellAction
    {
    public:
        CastEntanglingRootsCcAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "entangling roots on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool Execute(Event event);
    };

	class CastNaturesGraspAction : public CastBuffSpellAction
	{
	public:
		CastNaturesGraspAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's grasp") {}
	};

	class CastHibernateAction : public CastDebuffSpellAction
	{
	public:
		CastHibernateAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "hibernate") {}
	};

	class CastCurePoisonAction : public CastCureSpellAction
	{
	public:
		CastCurePoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure poison") {}
	};

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}
    };

	class CastAbolishPoisonAction : public CastCureSpellAction
	{
	public:
		CastAbolishPoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "abolish poison") {}
		virtual NextAction** getAlternatives();
	};

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}

        virtual NextAction** getAlternatives();
    };

    class CastBarskinAction : public CastBuffSpellAction
    {
    public:
        CastBarskinAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "barskin") {}
    };
}
