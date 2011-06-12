#pragma once
#include "Value.h"

namespace ai
{
    class FindTargetStrategy
    {
    public:
        FindTargetStrategy(AiManagerRegistry* aiRegistry)
        {
            result = NULL;
            this->aiRegistry = aiRegistry;
        }

    public:
        void CheckAttackers(Player* bot, Player* player);
        Unit* GetResult() { return result; }

    protected:
        virtual void CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager) = 0;
        void GetPlayerCount(Player* bot, Unit* creature, int* tankCount, int* dpsCount);

    protected:
        Unit* result;
        AiManagerRegistry* aiRegistry;

    protected:
        map<Unit*, int> tankCountCache;
        map<Unit*, int> dpsCountCache;
        set<Unit*> alreadyChecked;
    };

    class TargetValue : public CalculatedValue<Unit*>
	{
	public:
        TargetValue(AiManagerRegistry* const ai) : CalculatedValue<Unit*>(ai) {}

    protected:
        Unit* FindTarget(FindTargetStrategy* strategy);
    };
}
