#pragma once
using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;
    class FindTargetStrategy;

	class AiTargetManager : public AiManagerBase
	{
	public:
		AiTargetManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual Unit* GetPartyMemberWithoutAura(const char* spell);
		virtual Unit* GetPartyMinHealthPlayer();
		virtual Unit* GetDeadPartyMember();
		virtual Unit* GetPartyMemberToDispell(uint32 dispelType);
		virtual Unit* FindTargetForTank();
		virtual Unit* FindTargetForDps();
		virtual Unit* FindTargetForGrinding();
		virtual Unit* GetCurrentTarget();
        virtual Unit* FindCcTarget(const char* spell);
        virtual Unit* GetCurrentCcTarget(const char* spell);
        virtual void SetCurrentTarget(Unit* target);
		virtual Unit* GetSelf();
		virtual Unit* GetPet();
		virtual Unit* GetMaster();
		virtual Unit* GetLineTarget();
		Creature* GetCreature(ObjectGuid guid);
		GameObject* GetGameObject(ObjectGuid guid);

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	private:
		void RemoveNotInLOS( list<Unit *> &targets );


	};

};