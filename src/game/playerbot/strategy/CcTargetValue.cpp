#include "../../pchdef.h"
#include "../playerbot.h"
#include "CcTargetValue.h"

using namespace ai;

class FindTargetForCcStrategy : public FindTargetStrategy
{
public:
    FindTargetForCcStrategy(PlayerbotAI* ai, const char* spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

protected:
    virtual void CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager)
    {
        float threat = threatManager->getThreat(bot);
        Unit* creature = threatManager->getOwner();

        uint8 health = creature->GetHealthPercent();
        if (health < 75)
            return;

        int tankCount, dpsCount;
        GetPlayerCount(bot, creature, &tankCount, &dpsCount);

        if (tankCount || dpsCount || !ai->CanCastSpell(spell, creature))
            return;

        float minDistance = BOT_REACT_DISTANCE;
        Group* group = bot->GetGroup();
        if (group)
        {
            Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player *member = sObjectMgr.GetPlayer(itr->guid);
                if( !member || !member->isAlive() || member == bot)
                    continue;

                if (!ai->IsTank(member))
                    continue;

                float distance = member->GetDistance(creature);
                if (distance < minDistance)
                    minDistance = distance;
            }
        }

        if (minDistance < 20.0f)
            return;

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    const char* spell;
    float maxDistance;
};

Unit* CcTargetValue::Calculate()
{
    FindTargetForCcStrategy strategy(ai, qualifier.c_str());
    return FindTarget(&strategy);
}