#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiMoveManager : public AiManagerBase
	{
	public:
		AiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);

	public:
		virtual float GetDistanceTo(Unit* target);
        virtual void MoveTo(uint32 mapId, float x, float y, float z);
		virtual void MoveTo(Unit* target, float distance = 0.0f);
        virtual void MoveTo(WorldObject* target);
		virtual float GetFollowAngle();
		virtual void Follow(Unit* target, float distance = 2.0f);
		virtual void Follow(Unit* target, float distance, float angle);
		virtual bool Flee(Unit* target, float distance = SPELL_DISTANCE);
		virtual void Stay();
		virtual void StayCircle(float range = 2.0f);
		virtual void StayLine(float range = 2.0f);
		virtual void StayCombat(float range = 2.0f);
		virtual bool IsMoving(Unit* target);
		virtual void Attack(Unit* target);
		virtual void ReleaseSpirit();
		virtual void Resurrect();
		virtual void Revive();
        virtual void Summon();
        virtual bool IsBehind(Unit* target);
		virtual void Update();
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
        virtual void HandleMasterIncomingPacket(const WorldPacket& packet);
		virtual void UsePortal();
		virtual void SetInFront(const Unit* obj);

    private:
        bool IsMovingAllowed(Unit* target);
        bool IsMovingAllowed(uint32 mapId, float x, float y, float z);
        bool IsMovingAllowed();
        void UseMeetingStone(uint64 guid);
        void TeleportToMaster();
        void WaitForReach(float distance);
		void StayLine(vector<Player*> line, float diff, float cx, float cy, float cz, float orientation, float range);
		void UpdatePosition();

    private:
        vector<uint32> taxiNodes;
        ObjectGuid taxiMaster;
		Unit* lastFollow;
		uint32 lastAreaTrigger;
		float lastMoveToX, lastMoveToY, lastMoveToZ, lastMoveToOri;
	};

};
