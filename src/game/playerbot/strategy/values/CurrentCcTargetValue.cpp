#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "CurrentCcTargetValue.h"

using namespace ai;

class FindCurrentCcTargetStrategy : public FindTargetStrategy
{
public:
    FindCurrentCcTargetStrategy(PlayerbotAI* ai, const char* spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
    }

protected:
    virtual void CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager)
    {
        float threat = threatManager->getThreat(bot);
        Unit* creature = threatManager->getOwner();
        if (ai->HasAura(spell, creature))
            result = creature;
    }

private:
    const char* spell;
};


Unit* CurrentCcTargetValue::Calculate()
{
    FindCurrentCcTargetStrategy strategy(ai, qualifier.c_str());
    return FindTarget(&strategy);
}