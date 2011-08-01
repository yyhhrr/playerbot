#pragma once
#include "../Value.h"
#include "TargetValue.h"
#include "NearestUnitsValue.h"

namespace ai
{

    class AttackersValue : public NearestUnitsValue
	{
	public:
        AttackersValue(PlayerbotAI* ai) : NearestUnitsValue(ai) {}
        list<Unit*> Calculate();

	private:
        void AddAttackersOf(Group* group, set<Unit*>& targets);
        void AddAttackersOf(Player* player, set<Unit*>& targets);
		void RemoveNonThreating(set<Unit*>& targets);
		bool hasRealThreat(Unit* attacker);
    };
}
