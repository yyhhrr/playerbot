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

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	private:
		void RemoveNotInLOS( list<Unit *> &targets );


	};

};