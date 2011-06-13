#include "../../pchdef.h"
#include "../playerbot.h"
#include "../../MotionMaster.h"
#include "../../MovementGenerator.h"
#include "FleeManager.h"
#include "../../CreatureAI.h"
#include "LootObjectStack.h"
#include "../strategy/LastMovementValue.h"

using namespace ai;
using namespace std;

AiMoveManager::AiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
}

void AiMoveManager::ReleaseSpirit()
{
}

void AiMoveManager::Resurrect()
{
	Corpse* corpse = bot->GetCorpse();
	if (corpse)
	{
		time_t reclaimTime = corpse->GetGhostTime() + bot->GetCorpseReclaimDelay( corpse->GetType()==CORPSE_RESURRECTABLE_PVP );
		if (reclaimTime > time(0))
		{
			ostringstream os;
			os << "Will resurrect in ";
			os << (reclaimTime - time(0));
			os << " secs";
			aiRegistry->GetSocialManager()->TellMaster(os.str().c_str());
			ai->SetNextCheckDelay(reclaimTime - time(0));
		}
		else
			Revive();
	}
}

void AiMoveManager::Revive()
{
	PlayerbotChatHandler ch(ai->GetMaster());
	if (! ch.revive(*bot))
	{
		aiRegistry->GetSocialManager()->TellMaster(".. could not be revived ..");
		return;
	}
    ai->GetAiObjectContext()->GetValue<Unit*>("current target")->Set(NULL);
	bot->SetSelectionGuid(ObjectGuid());
}

void AiMoveManager::Summon()
{
    Player* master = ai->GetMaster();
    Map* masterMap = master->GetMap();
    Map* botMap = bot->GetMap();

    bool masterIsInInstance = (masterMap->IsDungeon() || masterMap->IsRaid() || masterMap->IsBattleGround());
    bool botIsInInstance = (botMap->IsDungeon() || botMap->IsRaid() || botMap->IsBattleGround());

    if ((masterIsInInstance && botIsInInstance) || (!masterIsInInstance && !botIsInInstance))
    {
        aiRegistry->GetSocialManager()->TellMaster("You can only summon me to your instance and back");
        return;
    }

    TeleportToMaster();
}

void AiMoveManager::TeleportToMaster()
{
    Player* master = bot->GetPlayerbotAI()->GetMaster();

    if (bot->IsWithinDistInMap(master, BOT_REACT_DISTANCE, true))
        return;

    PlayerbotChatHandler ch(master);
    if (!ch.teleport(*bot))
        aiRegistry->GetSocialManager()->TellMaster("You cannot summon me");
}

void AiMoveManager::UsePortal()
{
	
}

void AiMoveManager::HandleCommand(const string& text, Player& fromPlayer)
{
    if (text == "reset")
    {
        bot->GetMotionMaster()->Clear();
        bot->m_taxi.ClearTaxiDestinations();
    }
    else if (text == "summon")
    {
        Summon();
    }
}

void AiMoveManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
		// if a change in speed was detected for the master
		// make sure we have the same mount status
	case SMSG_FORCE_RUN_SPEED_CHANGE:
		{
			WorldPacket p(packet);
			uint64 guid = extractGuid(p);
			Player* master = ai->GetMaster();
			if (guid != master->GetGUID())
				return;
			if (master->IsMounted() && !bot->IsMounted())
			{
				if (!master->GetAurasByType(SPELL_AURA_MOUNTED).empty())
				{
					int32 master_speed1 = 0;
					int32 master_speed2 = 0;
					master_speed1 = ai->GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[1];
					master_speed2 = ai->GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[2];

					aiRegistry->GetSpellManager()->Mount(master_speed1, master_speed2);
				}
			}
			else if (!master->IsMounted() && bot->IsMounted())
			{
				aiRegistry->GetSpellManager()->Unmount();
			}
			return;
		}

		// handle flying acknowledgement
	case SMSG_MOVE_SET_CAN_FLY:
		{
			WorldPacket p(packet);
			uint64 guid = p.readPackGUID();
			if (guid != bot->GetGUID())
				return;

			bot->m_movementInfo.SetMovementFlags((MovementFlags)(MOVEFLAG_FLYING|MOVEFLAG_CAN_FLY));
			//bot->SetSpeed(MOVE_RUN, GetMaster()->GetSpeed(MOVE_FLIGHT) +0.1f, true);
			return;
		}

		// handle dismount flying acknowledgement
	case SMSG_MOVE_UNSET_CAN_FLY:
		{
			WorldPacket p(packet);
			uint64 guid = p.readPackGUID();
			if (guid != bot->GetGUID())
				return;
			bot->m_movementInfo.RemoveMovementFlag(MOVEFLAG_FLYING);
			//bot->SetSpeed(MOVE_RUN,GetMaster()->GetSpeedRate(MOVE_RUN),true);
			return;
		}

	case SMSG_RESURRECT_REQUEST:
		{
			if (bot->isAlive())
				return;
			WorldPacket p(packet);
			ObjectGuid guid;
			p >> guid;

			WorldPacket* const packet = new WorldPacket(CMSG_RESURRECT_RESPONSE, 8+1);
			*packet << guid;
			*packet << uint8(1);                        // accept
			bot->GetSession()->QueuePacket(packet);   // queue the packet to get around race condition
			return;
		}
	}

}

void AiMoveManager::UseMeetingStone(uint64 guid) 
{
    Player* master = bot->GetPlayerbotAI()->GetMaster();
    if (master->GetSelectionGuid().GetRawValue() != bot->GetGUID())
        return;

    GameObject* gameObject = master->GetMap()->GetGameObject(guid);
    if (!gameObject)
        return;

    const GameObjectInfo* goInfo = gameObject->GetGOInfo();
    if (!goInfo || goInfo->type != GAMEOBJECT_TYPE_SUMMONING_RITUAL)
        return;

    TeleportToMaster();
}

void AiMoveManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    switch (packet.GetOpcode())
    {
    case CMSG_ACTIVATETAXI:
        {
            WorldPacket p(packet);
            p.rpos(0);
            
            LastMovement& movement = aiRegistry->GetAi()->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();
            movement.taxiNodes.clear();
            movement.taxiNodes.resize(2);

            p >> movement.taxiMaster >> movement.taxiNodes[0] >> movement.taxiNodes[1];
            return;
        }
	case CMSG_ACTIVATETAXIEXPRESS:
		{
			WorldPacket p(packet);
			p.rpos(0);

			ObjectGuid guid;
			uint32 node_count;
			p >> guid >> node_count;

            LastMovement& movement = aiRegistry->GetAi()->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();
			movement.taxiNodes.clear();
			for (uint32 i = 0; i < node_count; ++i)
			{
				uint32 node;
				p >> node;
				movement.taxiNodes.push_back(node);
			}

			return;
		}
	case CMSG_GAMEOBJ_REPORT_USE:
        {
            WorldPacket p(packet);
            p.rpos(0);

            uint64 guid;
            p >> guid;

            UseMeetingStone(guid);
            return;
        }
	case CMSG_AREATRIGGER:
		{
            LastMovement& movement = aiRegistry->GetAi()->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();

			WorldPacket p(packet);
			p.rpos(0);
			p >> movement.lastAreaTrigger;
			Player* master = bot->GetPlayerbotAI()->GetMaster();
			//MoveTo(master->GetMapId(), master->GetPositionX(), master->GetPositionY(), master->GetPositionZ());
			
			//aiRegistry->GetSocialManager()->TellMaster("Ready to teleport");
			return;
		}
    }
}

void AiMoveManager::Update()
{
	if (!bot->GetAurasByType(SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED).empty())
	{
		bot->m_movementInfo.SetMovementFlags((MovementFlags)(MOVEFLAG_FLYING|MOVEFLAG_CAN_FLY));

		WorldPacket packet(CMSG_MOVE_SET_FLY);
		packet << bot->GetObjectGuid().WriteAsPacked();
		packet << bot->m_movementInfo;
		bot->SetMover(bot);
		bot->GetSession()->HandleMovementOpcodes(packet);
	}

	if (bot->IsMounted() && bot->IsFlying())
	{
		bot->m_movementInfo.SetMovementFlags((MovementFlags)(MOVEFLAG_FLYING|MOVEFLAG_CAN_FLY));
		bot->SetSpeedRate(MOVE_FLIGHT, 1.0f, true);
		bot->SetSpeedRate(MOVE_FLIGHT, ai->GetMaster()->GetSpeedRate(MOVE_FLIGHT), true);

		bot->SetSpeedRate(MOVE_RUN, 1.0f, true);
		bot->SetSpeedRate(MOVE_RUN, ai->GetMaster()->GetSpeedRate(MOVE_FLIGHT), true);
	}

	UpdatePosition();
}

void AiMoveManager::UpdatePosition() 
{
	if (ai->GetAiObjectContext()->GetValue<bool>("moving", "self target")->Get())
		return;

    LastMovement& movement = aiRegistry->GetAi()->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();
    movement.Update(bot);
}
