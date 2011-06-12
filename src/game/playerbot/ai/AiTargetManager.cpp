#include "../../pchdef.h"
#include "../playerbot.h"

#include "../../GridNotifiers.h"
#include "../../GridNotifiersImpl.h"
#include "../../CellImpl.h"

using namespace ai;
using namespace std;

Unit* AiTargetManager::GetSelf()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("self target")->Get();
}

Unit* AiTargetManager::GetMaster()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("master target")->Get();
}

Unit* AiTargetManager::GetCurrentTarget()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("current target")->Get();
}

void AiTargetManager::SetCurrentTarget(Unit* target) 
{
    ai->GetAiObjectContext()->GetValue<Unit*>("current target")->Set(target);
}

Unit* AiTargetManager::GetPartyMemberWithoutAura(const char* spell) 
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("party member without aura", spell)->Get();
}

Unit* AiTargetManager::GetPartyMinHealthPlayer()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("party member to heal")->Get();
}

Unit* AiTargetManager::GetDeadPartyMember() 
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("party member to resurrect")->Get();
}

Unit* AiTargetManager::GetLineTarget()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("line target")->Get();
}

Unit* AiTargetManager::FindTargetForTank()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("tank target")->Get();
}

Unit* AiTargetManager::FindTargetForDps()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("dps target")->Get();
}

Unit* AiTargetManager::FindCcTarget(const char* spell)
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("cc target", spell)->Get();
}

Unit* AiTargetManager::GetCurrentCcTarget(const char* spell)
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("current cc target", spell)->Get();
}

Unit* AiTargetManager::GetPet()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("pet target")->Get();
}

Unit* AiTargetManager::FindTargetForGrinding() 
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("grind target")->Get();
}

Unit* AiTargetManager::GetPartyMemberToDispell(uint32 dispelType)
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("party member to dispel", dispelType)->Get();
}


void AiTargetManager::HandleCommand(const string& text, Player& fromPlayer)
{
    if (text == "reset")
    {
        SetCurrentTarget(NULL);
    }
}

void AiTargetManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{

}




namespace MaNGOS
{

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
