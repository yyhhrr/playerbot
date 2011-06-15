#pragma once

namespace ai {
	class CastFeralChargeBearAction : public CastReachTargetSpellAction {
	public:
		CastFeralChargeBearAction(PlayerbotAI* ai) : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
	};

	class CastGrowlAction : public CastSpellAction {
	public:
		CastGrowlAction(PlayerbotAI* ai) : CastSpellAction(ai, "growl") {}
	};

	class CastMaulAction : public CastMeleeSpellAction {
	public:
		CastMaulAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "maul") {}
	};

	class CastBashAction : public CastMeleeSpellAction {
	public:
		CastBashAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "bash") {}
	};

	class CastSwipeAction : public CastMeleeSpellAction {
	public:
		CastSwipeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe") {}
	};

	class CastDemoralizingRoarAction : public CastMeleeSpellAction {
	public:
		CastDemoralizingRoarAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "demoralizing roar") {}
	};

	class CastMangleBearAction : public CastMeleeSpellAction {
	public:
		CastMangleBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mangle (bear)") {}
	};
	
	class CastSwipeBearAction : public CastMeleeSpellAction {
	public:
		CastSwipeBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe (bear)") {}
	};
}