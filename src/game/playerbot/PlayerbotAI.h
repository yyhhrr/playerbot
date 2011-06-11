#pragma once

#include "PlayerbotAIBase.h"
#include "strategy/AiObjectContext.h"
#include "strategy/Engine.h"

class Player;
class PlayerbotMgr;
class ChatHandler;

using namespace std;
using namespace ai;

namespace ai 
{
	class AiManagerRegistry;

	class MinValueCalculator {
	public:
		MinValueCalculator(float def = 0.0f) {
			param = NULL;
			minValue = def;
		}

	public:
		void probe(float value, void* p) {
			if (!param || minValue >= value) {
				minValue = value;
				param = p;
			}
		}

	public:
		void* param;
		float minValue;
	};
};

class PlayerbotAI : public PlayerbotAIBase
{
public:
	PlayerbotAI();
	PlayerbotAI(PlayerbotMgr* mgr, Player* bot);
	virtual ~PlayerbotAI();

public:
	void UpdateAI(uint32 elapsed);

    void UpdateNextCheckDelay();
    void HandleCommand(const string& text, Player& fromPlayer);
	void HandleBotOutgoingPacket(const WorldPacket& packet);
    void HandleMasterIncomingPacket(const WorldPacket& packet);
	void HandleTeleportAck();

    void ChangeStrategyIfNecessary();
    void DoNextAction();
    void DoSpecificAction(const char* name);
    void ChangeStrategy( const char* name, Engine* e );
    void ChangeCombatStrategy(const char* name) { ChangeStrategy(name, combatEngine); }
    void ChangeNonCombatStrategy(const char* name) { ChangeStrategy(name, nonCombatEngine); }
    bool ContainsStrategy(StrategyType type);
    void ReInitCurrentEngine();

public:
	Player* GetBot() { return bot; }
	Player* GetMaster() { return mgr->GetMaster(); }
	AiManagerRegistry* GetAiRegistry() { return aiRegistry; }
    AiGroupStatsManager* GetGroupStatsManager() { return mgr->GetGroupStatsManager(); }
    AiObjectContext* GetAiObjectContext() { return aiObjectContext; }

protected:
	Player* bot;
	PlayerbotMgr* mgr;
    AiObjectContext* aiObjectContext;
	AiManagerRegistry* aiRegistry;
    Engine* currentEngine;
    Engine* combatEngine;
    Engine* nonCombatEngine;
    map<uint16, string> packetHandlers;
};

