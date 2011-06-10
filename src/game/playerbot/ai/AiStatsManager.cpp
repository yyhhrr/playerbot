#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

uint8 AiStatsManager::GetHealthPercent(Unit* target)
{
    if (!target)
        return 100;
	return (static_cast<float> (target->GetHealth()) / target->GetMaxHealth()) * 100;
}

uint8 AiStatsManager::GetRage(Unit* target)
{
    if (!target)
        return 0;
	return (static_cast<float> (target->GetPower(POWER_RAGE)));
}

uint8 AiStatsManager::GetEnergy(Unit* target)
{
    if (!target)
        return 0;
	return (static_cast<float> (target->GetPower(POWER_ENERGY)));
}

uint8 AiStatsManager::GetManaPercent(Unit* target)
{
    if (!target)
        return 100;
	return (static_cast<float> (target->GetPower(POWER_MANA)) / target->GetMaxPower(POWER_MANA)) * 100;
}

uint8 AiStatsManager::GetComboPoints(Player* target) 
{
    if (!target)
        return 0;
	return target->GetComboPoints();
}

bool AiStatsManager::HasMana(Unit* target)
{
    if (!target)
        return false;
	// TODO: base value?
	return target->GetPower(POWER_MANA);
}

bool AiStatsManager::IsDead(Unit* target)
{
    if (!target)
        return false;
	return target->getDeathState() != ALIVE; 
}

int AiStatsManager::GetMyAttackerCount()
{
    return bot->getAttackers().size();
}

bool AiStatsManager::HasAggro(Unit* target)
{
	if (!target)
		return true;

	HostileReference *ref = bot->getHostileRefManager().getFirst();
	if (!ref)
		return true; // simulate as target is not atacking anybody yet

	while( ref )
	{
		ThreatManager *threatManager = ref->getSource();
		Unit *attacker = threatManager->getOwner();
		Unit *victim = attacker->getVictim();
		if (victim == bot && target == attacker)
			return true;
		ref = ref->next();
	}
	return false;
}


bool AiStatsManager::IsMounted()
{
	return bot->IsMounted();
}



void AiStatsManager::HandleCommand(const string& text, Player& fromPlayer)
{
}

void AiStatsManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{

}

bool AiStatsManager::IsTank(Player* player)
{
	PlayerbotAI* botAi = player->GetPlayerbotAI();
	if (botAi)
		return botAi->ContainsStrategy(STRATEGY_TYPE_TANK);

	switch (player->getClass()) 
	{
		case CLASS_DEATH_KNIGHT:
		case CLASS_PALADIN:
		case CLASS_WARRIOR:
			return true;
		case CLASS_DRUID:
			return aiRegistry->GetSpellManager()->HasAnyAuraOf(player, "bear form", "dire bear form");
	}
	return false;
}

bool AiStatsManager::IsDps(Player* player)
{
	return !IsTank(player);
}

void AiStatsManager::Update()
{
}

int AiStatsManager::GetAttackerCount(float distance)
{
    return ai->GetGroupStatsManager()->GetAttackerCount();
}

int AiStatsManager::GetAttackerCount(Unit* target, float range)
{
    if (!target) 
        return 0;

    int count = 1;

    AttackerMap attackers = ai->GetGroupStatsManager()->GetAttackers();
    for (AttackerMapIterator i = attackers.begin(); i != attackers.end(); i++)
    {
        Unit* unit = sObjectAccessor.GetUnit(*bot, i->first);
        if (!unit || unit == target)
            continue;

        float distance = unit->GetDistance(target);
        if (distance <= range)
            count++;
    }
    
    return count;
}

float AiStatsManager::GetBalancePercent()
{
    return ai->GetGroupStatsManager()->GetBalancePercent();
}

