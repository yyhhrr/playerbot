#include "../../pchdef.h"
#include "../playerbot.h"
#include "FindTargetStrategy.h"

#include "../../GridNotifiers.h"
#include "../../GridNotifiersImpl.h"
#include "../../CellImpl.h"

using namespace ai;
using namespace std;

Unit* AiTargetManager::GetCurrentTarget()
{
	if (selection.IsEmpty())
		return NULL;

	Unit* unit = sObjectAccessor.GetUnit(*bot, selection);
	if (unit && !bot->IsWithinLOSInMap(unit))
		return NULL;

	return unit;
}

void AiTargetManager::SetCurrentTarget(Unit* target) 
{
	if (!target)
	{
		selection = ObjectGuid();
		return;
	}

	selection = target->GetObjectGuid(); 
}

Unit* AiTargetManager::GetPartyMemberWithoutAura(const char* spell) 
{
	return FindPartyMember(&AiTargetManager::PlayerWithoutAuraPredicate, (void*)spell); 
}

Unit* AiTargetManager::GetPartyMinHealthPlayer()
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	MinValueCalculator calc(100);
	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (!CheckPredicate(player, NULL, NULL) || !player->isAlive())
			continue;

		uint8 health = aiRegistry->GetStatsManager()->GetHealthPercent(player);
		if (health < 25 || !IsTargetOfHealingSpell(player))
			calc.probe(health, player);

		Pet* pet = player->GetPet();
		if (pet && CanHealPet(pet)) 
		{
			health = aiRegistry->GetStatsManager()->GetHealthPercent(pet);
			if (health < 25 || !IsTargetOfHealingSpell(player))
				calc.probe(health, player);
		}
	}
	return (Unit*)calc.param;
}

Unit* AiTargetManager::GetDeadPartyMember() 
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (CheckPredicate(player, NULL, NULL) && !player->isAlive() && !IsTargetOfResurrectSpell(player))
			return player;
	}
	return NULL;
}

Unit* AiTargetManager::FindPartyMember(FindPlayerPredicate predicate, void* param)
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (CheckPredicate(player, predicate, param))
			return player;

		Pet* pet = player->GetPet();
		if (pet && CanHealPet(pet) && CheckPredicate(player, predicate, param))
			return player;
	}
	return NULL;
}

bool AiTargetManager::CheckPredicate(Unit* player, FindPlayerPredicate predicate, void *param) 
{
	return (player != bot && 
		bot->GetDistance(player) < 50.0f &&
		bot->IsWithinLOS(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()) &&
		(predicate==NULL || (this->*predicate)(player, param)));
}

bool AiTargetManager::PlayerWithoutAuraPredicate(Unit* player, void *param )
{
	return player->isAlive() && !aiRegistry->GetSpellManager()->HasAura((const char*)param, player);
}


bool AiTargetManager::IsHealingSpell(SpellEntry const* spell) {
	for (int i=0; i<3; i++) {
		if (spell->Effect[i] == SPELL_EFFECT_HEAL ||
			spell->Effect[i] == SPELL_EFFECT_HEAL_MAX_HEALTH ||
			spell->Effect[i] == SPELL_EFFECT_HEAL_MECHANICAL || 
			spell->Effect[i] == SPELL_EFFECT_HEAL_PCT)
			return true;
	}
	return false;
}

bool AiTargetManager::IsResurrectSpell(SpellEntry const* spell) {
	for (int i=0; i<3; i++) {
		if (spell->Effect[i] == SPELL_EFFECT_RESURRECT || 
			spell->Effect[i] == SPELL_EFFECT_RESURRECT_NEW || 
			spell->Effect[i] == SPELL_EFFECT_SELF_RESURRECT)
			return true;
	}
	return false;
}


bool AiTargetManager::IsTargetOfHealingSpell(Player* target) {
	return IsTargetOfSpellCast(target, &AiTargetManager::IsHealingSpell);
}

bool AiTargetManager::IsTargetOfResurrectSpell(Player* target) {
	return IsTargetOfSpellCast(target, &AiTargetManager::IsResurrectSpell);
}

bool AiTargetManager::IsTargetOfSpellCast(Player* target, SpellEntryPredicate predicate) 
{
	Group* group = bot->GetGroup();
	ObjectGuid targetGuid = target ? target->GetObjectGuid() : bot->GetObjectGuid();
    ObjectGuid corpseGuid = target && target->GetCorpse() ? target->GetCorpse()->GetObjectGuid() : ObjectGuid();

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (player == bot)
			continue;

		if (player->IsNonMeleeSpellCasted(true)) 
		{
			for (int type = CURRENT_GENERIC_SPELL; type < CURRENT_MAX_SPELL; type++) {
				Spell* spell = player->GetCurrentSpell((CurrentSpellTypes)type);
                if (spell && (this->*predicate)(spell->m_spellInfo)) { 
                    ObjectGuid unitTarget = spell->m_targets.getUnitTargetGuid();
                    if (unitTarget == targetGuid)
                        return true;
                    
                    ObjectGuid corpseTarget = spell->m_targets.getCorpseTargetGuid();
                    if (corpseTarget == corpseGuid)
                        return true;
                }
			}
		}
	}

	return false;
}

Unit* AiTargetManager::GetPartyMemberToDispell(uint32 dispelType)
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;
	
	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if( !player || !player->isAlive() || player == bot)
			continue;

		if (HasAuraToDispel(player, dispelType))
			return player;

		Pet* pet = player->GetPet();
		if (pet && CanHealPet(pet) && HasAuraToDispel(pet, dispelType))
			return pet;
	}

	return NULL;
}


bool AiTargetManager::HasAuraToDispel(Unit* player, uint32 dispelType) 
{
	for (uint32 type = SPELL_AURA_NONE; type < TOTAL_AURAS; ++type)
	{
		Unit::AuraList auras = player->GetAurasByType((AuraType)type);
		for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
		{
			Aura* aura = *itr;
			const SpellEntry* entry = aura->GetSpellProto();
			uint32 spellId = entry->Id;
			if (IsPositiveSpell(spellId))
				continue;

			if (canDispel(entry, dispelType))
				return true;
		}
	}
	return false;
}

bool AiTargetManager::canDispel(const SpellEntry* entry, uint32 dispelType) {
	if (entry->Dispel == dispelType) {
		return !entry->SpellName[0] ||
			(strcmpi((const char*)entry->SpellName[0], "demon skin") &&
			strcmpi((const char*)entry->SpellName[0], "mage armor") &&
			strcmpi((const char*)entry->SpellName[0], "frost armor") &&
			strcmpi((const char*)entry->SpellName[0], "ice armor"));
	}
	return false;
}

Player* AiTargetManager::GetSelf()
{
	return bot;
}

Player* AiTargetManager::GetMaster()
{
	return ai->GetMaster();
}

Player* AiTargetManager::GetLineTarget()
{
	Player* master = GetMaster();

	Group* group = master->GetGroup();
	if (!group)
		return NULL;
	
	Player *prev = master;
	Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
	for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
	{
		Player *player = sObjectMgr.GetPlayer(itr->guid);
		if( !player || !player->isAlive() || player == master)
			continue;

		if (player == bot)
			return prev;

		prev = player;
	}

	return master;
}

Unit* AiTargetManager::GetPet()
{
	return bot->GetPet();
}

bool AiTargetManager::CanHealPet(Pet* pet) 
{
	PetType type = pet->getPetType();
	return type != SUMMON_PET && type != MINI_PET;
}

void AiTargetManager::HandleCommand(const string& text, Player& fromPlayer)
{
    if (text == "reset")
    {
        ResetTarget();
    }
	else if (text == "los")
	{
		AiSocialManager* aiSocialManager = aiRegistry->GetSocialManager();
		
		aiSocialManager->ListUnits("--- Targets ---", FindPossibleTargets());
		aiSocialManager->ListUnits("--- NPCs ---", FindNearestNpcs());
		aiSocialManager->ListUnits("--- Corpses ---", FindNearestCorpses());
        list<GameObject*> gos = *aiRegistry->GetAi()->GetAiObjectContext()->GetValue<list<GameObject*>>("nearest game objects");
		aiSocialManager->ListGameObjects("--- Game objects ---", gos);
	}
}

void AiTargetManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{

}

Unit* AiTargetManager::FindTarget(FindTargetStrategy* strategy)
{
	Group* group = bot->GetGroup();
	if (!group)
	{
		strategy->CheckAttackers(bot, bot);
		return strategy->GetResult();
	}

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* member = gref->getSource();
		if (!member || !member->isAlive() || !member->IsWithinLOSInMap(member))
			continue;

		strategy->CheckAttackers(bot, member);
	}

	return strategy->GetResult();
}

Unit* AiTargetManager::FindTargetForTank()
{
	FindTargetForTankStrategy strategy(aiRegistry);
	return FindTarget(&strategy);
}

Unit* AiTargetManager::FindTargetForDps()
{
	FindTargetForDpsStrategy strategy(aiRegistry);
	return FindTarget(&strategy);
}

Unit* AiTargetManager::FindCcTarget(const char* spell)
{
    FindTargetForCcStrategy strategy(aiRegistry, spell);
    return FindTarget(&strategy);
}

Unit* AiTargetManager::GetCurrentCcTarget(const char* spell)
{
    FindCurrentCcTargetStrategy strategy(aiRegistry, spell);
    return FindTarget(&strategy);
}


namespace MaNGOS
{
	class AnyDeadUnitInObjectRangeCheck
	{
	public:
		AnyDeadUnitInObjectRangeCheck(WorldObject const* obj, float range) : i_obj(obj), i_range(range) {}
		WorldObject const& GetFocusObject() const { return *i_obj; }
		bool operator()(Unit* u)
		{
			return !u->isAlive() && i_obj->IsWithinDistInMap(u, i_range);
		}
	private:
		WorldObject const* i_obj;
		float i_range;
	};

	class UnitByGuidInRangeCheck
	{
	public:
		UnitByGuidInRangeCheck(WorldObject const* obj, ObjectGuid guid, float range) : i_obj(obj), i_range(range), i_guid(guid) {}
		WorldObject const& GetFocusObject() const { return *i_obj; }
		bool operator()(Unit* u)
		{
			return u->GetObjectGuid() == i_guid && i_obj->IsWithinDistInMap(u, i_range);
		}
	private:
		WorldObject const* i_obj;
		float i_range;
		ObjectGuid i_guid;
	};

	class GameObjectByGuidInRangeCheck
	{
	public:
		GameObjectByGuidInRangeCheck(WorldObject const* obj, ObjectGuid guid, float range) : i_obj(obj), i_range(range), i_guid(guid) {}
		WorldObject const& GetFocusObject() const { return *i_obj; }
		bool operator()(GameObject* u)
		{
			if (u && i_obj->IsWithinDistInMap(u, i_range) && u->isSpawned() && u->GetGOInfo() && u->GetObjectGuid() == i_guid)
				return true;

			return false;
		}
	private:
		WorldObject const* i_obj;
		float i_range;
		ObjectGuid i_guid;
	};

};

list<Unit*> AiTargetManager::FindNearestCorpses(float range)
{
	list<Unit *> targets;

	MaNGOS::AnyDeadUnitInObjectRangeCheck u_check(bot,  range);
	MaNGOS::UnitListSearcher<MaNGOS::AnyDeadUnitInObjectRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(bot, searcher, range);

	RemoveNotInLOS(targets);
	return targets;
}

list<Unit*> AiTargetManager::FindPossibleTargets(float range)
{
	list<Unit *> targets;

	MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, bot, range);
	MaNGOS::UnitListSearcher<MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(bot, searcher, range);

	RemoveNotInLOS(targets);
	return targets;
}

list<Unit*> AiTargetManager::FindNearestNpcs(float range)
{
	list<Unit *> targets;

	MaNGOS::AnyFriendlyUnitInObjectRangeCheck u_check(bot, range);
	MaNGOS::UnitListSearcher<MaNGOS::AnyFriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(bot, searcher, range);

	RemoveNotInLOS(targets);
	return targets;
}

int AiTargetManager::GetTargetingPlayerCount( Unit* unit ) 
{
	Group* group = bot->GetGroup();
	if (!group)
		return 0;
	
	int count = 0;
	Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
	for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
	{
		Player *member = sObjectMgr.GetPlayer(itr->guid);
		if( !member || !member->isAlive() || member == bot)
			continue;

		PlayerbotAI* ai = member->GetPlayerbotAI();
		if ((ai && ai->GetAiRegistry()->GetTargetManager()->GetCurrentTarget() == unit) ||
		    (!ai && member->GetSelectionGuid() == unit->GetObjectGuid()))
			count++;
	}
	
	return count;
}

Unit* AiTargetManager::FindTargetForGrinding() 
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	Unit* target = NULL;
	int assistCount = 0;
	while (!target && assistCount < group->GetMembersCount())
	{
		target = FindTargetForGrinding(assistCount++);
	}
	
	return target;
}

Unit* AiTargetManager::FindTargetForGrinding(int assistCount) 
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	list<Unit *> targets = FindPossibleTargets();

    if(targets.empty())
        return NULL;

	float distance = 0;
	Unit* result = NULL;
    for(list<Unit *>::iterator tIter = targets.begin(); tIter != targets.end(); tIter++)
    {
		Unit* unit = *tIter;

		if (abs(bot->GetPositionZ() - unit->GetPositionZ()) > SPELL_DISTANCE)
			continue;
		
		if (GetTargetingPlayerCount(unit) > assistCount)
			continue;

		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *member = sObjectMgr.GetPlayer(itr->guid);
			if( !member || !member->isAlive())
				continue;

			if (GetMaster()->GetDistance(unit) >= BOT_GRIND_DISTANCE)
				continue;

			float d = member->GetDistance(unit);
			if (!result || d < distance)
			{
				distance = d;
				result = unit;
			}
		}
	}

	return result;
}

void AiTargetManager::RemoveNotInLOS( list<Unit *> &targets ) 
{
	for(list<Unit *>::iterator tIter = targets.begin(); tIter != targets.end();)
	{
		if(!bot->IsWithinLOSInMap(*tIter))
		{
			list<Unit *>::iterator tIter2 = tIter;
			++tIter;
			targets.erase(tIter2);
		}
		else
			++tIter;
	}
}

Creature* AiTargetManager::GetCreature(ObjectGuid guid)
{
	if (!guid)
		return NULL;

	if (bot->GetMapId() != aiRegistry->GetTargetManager()->GetMaster()->GetMapId())
		return NULL;

	list<Unit *> targets;

	MaNGOS::UnitByGuidInRangeCheck u_check(bot, guid, BOT_SIGHT_DISTANCE);
	MaNGOS::UnitListSearcher<MaNGOS::UnitByGuidInRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(bot, searcher, BOT_SIGHT_DISTANCE);
	
	for(list<Unit *>::iterator i = targets.begin(); i != targets.end(); i++)
	{
		Creature* creature = dynamic_cast<Creature*>(*i);
		if (creature)
			return creature;
	}
	
	return NULL;
}

GameObject* AiTargetManager::GetGameObject(ObjectGuid guid)
{
	if (!guid)
		return NULL;
	
	if (bot->GetMapId() != aiRegistry->GetTargetManager()->GetMaster()->GetMapId())
		return NULL;

	list<GameObject*> targets;

	MaNGOS::GameObjectByGuidInRangeCheck u_check(bot, guid, BOT_SIGHT_DISTANCE);
	MaNGOS::GameObjectListSearcher<MaNGOS::GameObjectByGuidInRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(bot, searcher, BOT_SIGHT_DISTANCE);

	for(list<GameObject*>::iterator i = targets.begin(); i != targets.end(); i++)
	{
		GameObject* go = *i;
		if (go && go->isSpawned())
			return go;
	}

	return NULL;
}
