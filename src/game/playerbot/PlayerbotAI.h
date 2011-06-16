#pragma once

#include "PlayerbotMgr.h"
#include "PlayerbotAIBase.h"
#include "strategy/AiObjectContext.h"
#include "strategy/Engine.h"

class Player;
class PlayerbotMgr;
class ChatHandler;

using namespace std;
using namespace ai;

class PlayerbotChatHandler: protected ChatHandler
{
public:
    explicit PlayerbotChatHandler(Player* pMasterPlayer) : ChatHandler(pMasterPlayer) {}
    bool revive(const Player& botPlayer) { return HandleReviveCommand((char*)botPlayer.GetName()); }
    bool teleport(const Player& botPlayer) { return HandleNamegoCommand((char*)botPlayer.GetName()); }
    void sysmessage(const char *str) { SendSysMessage(str); }
    bool dropQuest(const char *str) { return HandleQuestRemoveCommand((char*)str); }
    uint32 extractQuestId(const char *str);
};

namespace ai 
{
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
	PlayerbotAI(PlayerbotMgr* mgr, Player* bot, NamedObjectContext<UntypedValue>* sharedValues);
	virtual ~PlayerbotAI();

public:
	void UpdateAI(uint32 elapsed);

    void UpdateNextCheckDelay();
    void HandleCommand(const string& text, Player& fromPlayer);
	void HandleBotOutgoingPacket(const WorldPacket& packet);
    void HandleMasterIncomingPacket(const WorldPacket& packet);
	void HandleTeleportAck();
    void ChangeStrategyIfNecessary();
    void ChangeEngine(Engine* engine);
    void DoNextAction();
    void DoSpecificAction(const char* name);
    void ChangeStrategy( const char* name, Engine* e );
    void ChangeCombatStrategy(const char* name) { ChangeStrategy(name, combatEngine); }
    void ChangeNonCombatStrategy(const char* name) { ChangeStrategy(name, nonCombatEngine); }
    bool ContainsStrategy(StrategyType type);
    void ReInitCurrentEngine();
    bool IsTank(Player* player);
    Creature* GetCreature(ObjectGuid guid);
    GameObject* GetGameObject(ObjectGuid guid);
    void TellMaster(ostringstream &stream) { TellMaster(stream.str().c_str()); }
    void TellMaster(string &text) { TellMaster(text.c_str()); }
    void TellMaster(const char* text);
    void TellMaster(LogLevel level, const char* text);
    void WaitForSpellCast();
    void SpellInterrupted(uint32 spellid);
    int32 CalculateGlobalCooldown(uint32 spellid);
    void InterruptSpell();
    void RemoveAura(const char* name);

    virtual bool CanCastSpell(const char* name, Unit* target);
    virtual bool CastSpell(const char* name, Unit* target);
    virtual bool HasAura(const char* spellName, Unit* player);
    virtual bool HasAnyAuraOf(Unit* player, ...);

    virtual bool IsSpellCasting(Unit* player);
    virtual bool HasAuraToDispel(Unit* player, uint32 dispelType);
    bool CanCastSpell(uint32 spellid, Unit* target);

    bool HasAura(uint32 spellId, const Unit* player);
    bool CastSpell(uint32 spellId, Unit* target);
    bool canDispel(const SpellEntry* entry, uint32 dispelType);

public:
	Player* GetBot() { return bot; }
    Player* GetMaster() { return mgr ? mgr->GetMaster() : NULL; }
    AiObjectContext* GetAiObjectContext() { return aiObjectContext; }

protected:
	Player* bot;
	PlayerbotMgr* mgr;
    AiObjectContext* aiObjectContext;
    Engine* currentEngine;
    Engine* combatEngine;
    Engine* nonCombatEngine;
    Engine* deadEngine;
    map<uint16, string> packetHandlers;
    map<uint16, string> masterPacketHandlers;
};

