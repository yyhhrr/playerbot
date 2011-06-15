#pragma once

namespace ai {
	class CastFeralChargeCatAction : public CastReachTargetSpellAction 
	{
	public:
		CastFeralChargeCatAction(PlayerbotAI* ai) : CastReachTargetSpellAction(ai, "feral charge - cat", 1.5f) {}
	};

	class CastCatSpellAction : public CastSpellAction 
	{
	public:
		CastCatSpellAction(PlayerbotAI* ai, const char* spell) : CastSpellAction(ai, spell) {}
		
		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastSpellAction::getPrerequisites());
		}
	};


	class CastCatBuffSpellAction : public CastBuffSpellAction 
	{
	public:
		CastCatBuffSpellAction(PlayerbotAI* ai, const char* spell) : CastBuffSpellAction(ai, spell) {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastBuffSpellAction::getPrerequisites());
		}
	};

	class CastCatMeleeSpellAction : public CastMeleeSpellAction 
	{
	public:
		CastCatMeleeSpellAction(PlayerbotAI* ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
		}
	};

	class CastCowerAction : public CastBuffSpellAction 
	{
	public:
		CastCowerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cower") {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastBuffSpellAction::getPrerequisites());
		}
	};


	class CastBerserkAction : public CastCatBuffSpellAction 
	{
	public:
		CastBerserkAction(PlayerbotAI* ai) : CastCatBuffSpellAction(ai, "berserk") {}
	};

	class CastTigersFuryAction : public CastCatBuffSpellAction 
	{
	public:
		CastTigersFuryAction(PlayerbotAI* ai) : CastCatBuffSpellAction(ai, "tiger's fury") {}
	};
	
	class CastRakeAction : public CastDebuffSpellAction 
	{
	public:
		CastRakeAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "rake") {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), new NextAction("cat form"), NULL), CastDebuffSpellAction::getPrerequisites());
		}
	};


	class CastClawAction : public CastCatMeleeSpellAction {
	public:
		CastClawAction(PlayerbotAI* ai) : CastCatMeleeSpellAction(ai, "claw") {}
	};

	class CastMangleCatAction : public CastCatMeleeSpellAction {
	public:
		CastMangleCatAction(PlayerbotAI* ai) : CastCatMeleeSpellAction(ai, "mangle (cat)") {}
	};

	class CastSwipeCatAction : public CastMeleeSpellAction {
	public:
		CastSwipeCatAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe (cat)") {}
	};

	class CastFerociousBiteAction : public CastCatMeleeSpellAction {
	public:
		CastFerociousBiteAction(PlayerbotAI* ai) : CastCatMeleeSpellAction(ai, "ferocious bite") {}
	};


	class CastRipAction : public CastCatMeleeSpellAction {
	public:
		CastRipAction(PlayerbotAI* ai) : CastCatMeleeSpellAction(ai, "rip") {}
	};



}