#include "../pchdef.h"
#include "playerbot.h"

#include "strategy/ExternalEventHelper.h"
#include "ai/AiFactory.h"

#include "../GridNotifiers.h"
#include "../GridNotifiersImpl.h"
#include "../CellImpl.h"
#include "strategy/LastMovementValue.h"
#include "strategy/LogLevelAction.h"

using namespace ai;
using namespace std;

vector<string>& split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    return split(s, delim, elems);
}


char * strstri (const char * str1, const char * str2)
{
    char *cp = (char *) str1;
    char *s1, *s2;

    if ( !*str2 )
        return((char *)str1);

    while (*cp)
    {
        s1 = cp;
        s2 = (char *) str2;

        while ( *s1 && *s2 && !(tolower(*s1)-tolower(*s2)) )
            s1++, s2++;

        if (!*s2)
            return(cp);

        cp++;
    }

    return(NULL);
}

uint32 extractMoney(const string& text)
{
    // if user specified money in ##g##s##c format
    string acum = "";
    uint32 copper = 0;
    for (uint8 i = 0; i < text.length(); i++)
    {
        if (text[i] == 'g')
        {
            copper += (atol(acum.c_str()) * 100 * 100);
            acum = "";
        }
        else if (text[i] == 'c')
        {
            copper += atol(acum.c_str());
            acum = "";
        }
        else if (text[i] == 's')
        {
            copper += (atol(acum.c_str()) * 100);
            acum = "";
        }
        else if (text[i] == ' ')
            break;
        else if (text[i] >= 48 && text[i] <= 57)
            acum += text[i];
        else
        {
            copper = 0;
            break;
        }
    }
    return copper;
}

void extractItemIds(const string& text, list<uint32>& itemIds)
{
    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hitem:", pos);
        if (i == -1)
            break;
        pos = i + 6;
        int endPos = text.find(':', pos);
        if (endPos == -1)
            break;
        string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos;
        if (id)
            itemIds.push_back(id);
    }
}

PlayerbotAI::PlayerbotAI() : PlayerbotAIBase()
{
	aiRegistry = NULL;
    aiObjectContext = NULL;
    combatEngine = NULL;
    nonCombatEngine = NULL;
    currentEngine = NULL;
    deadEngine = NULL;
}

PlayerbotAI::PlayerbotAI(PlayerbotMgr* mgr, Player* bot, NamedObjectContext<UntypedValue>* sharedValues) : PlayerbotAIBase()
{
	this->mgr = mgr;
	this->bot = bot;
    aiRegistry = new AiManagerRegistry(this);

    aiObjectContext = AiFactory::createAiObjectContext(bot, aiRegistry);
    aiObjectContext->AddShared(sharedValues);

    combatEngine = AiFactory::createCombatEngine(bot, aiRegistry, aiObjectContext);
    nonCombatEngine = AiFactory::createNonCombatEngine(bot, aiRegistry, aiObjectContext);
    deadEngine = AiFactory::createDeadEngine(bot, aiRegistry, aiObjectContext);

    currentEngine = nonCombatEngine;

    masterPacketHandlers[CMSG_GAMEOBJ_REPORT_USE] = "use game object";
    masterPacketHandlers[CMSG_AREATRIGGER] = "area trigger";
    masterPacketHandlers[CMSG_GAMEOBJ_USE] = "use game object";
    masterPacketHandlers[CMSG_LOOT_ROLL] = "loot roll";

    masterPacketHandlers[CMSG_GOSSIP_HELLO] = "gossip hello";
    masterPacketHandlers[CMSG_QUESTGIVER_HELLO] = "gossip hello";
    masterPacketHandlers[CMSG_QUESTGIVER_COMPLETE_QUEST] = "complete quest";
    masterPacketHandlers[CMSG_QUESTGIVER_ACCEPT_QUEST] = "accept quest";
    
    masterPacketHandlers[CMSG_ACTIVATETAXI] = "activate taxi";
    masterPacketHandlers[CMSG_ACTIVATETAXIEXPRESS] = "activate taxi";
    
    packetHandlers[SMSG_QUESTGIVER_QUEST_DETAILS] = "quest share";
    packetHandlers[SMSG_GROUP_INVITE] = "group invite";
    packetHandlers[BUY_ERR_NOT_ENOUGHT_MONEY] = "not enough money";
    packetHandlers[BUY_ERR_REPUTATION_REQUIRE] = "not enough reputation";
    packetHandlers[SMSG_GROUP_SET_LEADER] = "group set leader";
    packetHandlers[SMSG_FORCE_RUN_SPEED_CHANGE] = "check mount state";
    packetHandlers[SMSG_RESURRECT_REQUEST] = "resurrect request";
    packetHandlers[SMSG_INVENTORY_CHANGE_FAILURE] = "cannot equip";
    packetHandlers[SMSG_TRADE_STATUS] = "trade status";

}

PlayerbotAI::~PlayerbotAI()
{
    if (combatEngine) 
        delete combatEngine;

    if (nonCombatEngine) 
        delete nonCombatEngine;

    if (deadEngine)
        delete deadEngine;

    if (aiObjectContext)
        delete aiObjectContext;

	if (aiRegistry)
		delete aiRegistry;
}

void PlayerbotAI::UpdateAI(uint32 elapsed)
{
	ChangeStrategyIfNecessary();

	if (!CanUpdateAI() || bot->IsBeingTeleported())
		return;

	DoNextAction();
	YieldThread();
}

void PlayerbotAI::HandleTeleportAck()
{
	bot->GetMotionMaster()->Clear(true);
	if (bot->IsBeingTeleportedNear())
	{
		WorldPacket p = WorldPacket(MSG_MOVE_TELEPORT_ACK, 8 + 4 + 4);
		p.appendPackGUID(bot->GetGUID());
		p << (uint32) 0; // supposed to be flags? not used currently
		p << (uint32) time(0); // time - not currently used
		bot->GetSession()->HandleMoveTeleportAckOpcode(p);
	}
	else if (bot->IsBeingTeleportedFar())
		bot->GetSession()->HandleMoveWorldportAckOpcode();
}

void PlayerbotAI::HandleCommand(const string& text, Player& fromPlayer)
{
	// ignore any messages from Addons
	if (text.empty() ||
		text.find("X-Perl") != wstring::npos ||
		text.find("HealBot") != wstring::npos ||
		text.find("LOOT_OPENED") != wstring::npos ||
		text.find("CTRA") != wstring::npos)
		return;

	if (fromPlayer.GetGuildId() != bot->GetGuildId() || !bot->GetGuildId())
	    return;

	AiManagerBase** managers = aiRegistry->GetManagers();

    if (text.size() > 2 && text.substr(0, 2) == "d " || text.size() > 3 && text.substr(0, 3) == "do ")
    {
        std::string action = text.substr(text.find(" ") + 1);
        DoSpecificAction(action.c_str());
    }

    else if (text.size() > 3 && text.substr(0, 3) == "co ")
    {
        std::string strategy = text.substr(text.find(" ") + 1);
        ChangeCombatStrategy(strategy.c_str());
    }

    else if (text.size() > 3 && text.substr(0, 3) == "nc ")
    {
        std::string strategy = text.substr(text.find(" ") + 1);
        ChangeNonCombatStrategy(strategy.c_str());
    }
    else if (text == "reset")
    {
        combatEngine->Init();
        nonCombatEngine->Init();
        currentEngine = nonCombatEngine;
        nextAICheckTime = 0;
        aiObjectContext->GetValue<Unit*>("current target")->Set(NULL);
        
        bot->GetMotionMaster()->Clear();
        bot->m_taxi.ClearTaxiDestinations();
    }


	for (int i=0; i<aiRegistry->GetManagerCount(); i++)
		managers[i]->HandleCommand(text, fromPlayer);

    ExternalEventHelper helper(aiObjectContext);
    helper.ParseChatCommand(text);
}

void PlayerbotAI::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	AiManagerBase** managers = aiRegistry->GetManagers();
	for (int i=0; i<aiRegistry->GetManagerCount(); i++)
		managers[i]->HandleBotOutgoingPacket(packet);

    ExternalEventHelper helper(aiObjectContext);
    helper.HandlePacket(packetHandlers, packet);

    switch (packet.GetOpcode())
    {
    case SMSG_MOVE_SET_CAN_FLY:
        {
            WorldPacket p(packet);
            uint64 guid = p.readPackGUID();
            if (guid != bot->GetGUID())
                return;

            bot->m_movementInfo.SetMovementFlags((MovementFlags)(MOVEFLAG_FLYING|MOVEFLAG_CAN_FLY));
            return;
        }
    case SMSG_MOVE_UNSET_CAN_FLY:
        {
            WorldPacket p(packet);
            uint64 guid = p.readPackGUID();
            if (guid != bot->GetGUID())
                return;
            bot->m_movementInfo.RemoveMovementFlag(MOVEFLAG_FLYING);
            return;
        }
    }
}

void PlayerbotAI::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    AiManagerBase** managers = aiRegistry->GetManagers();
    for (int i=0; i<aiRegistry->GetManagerCount(); i++)
        managers[i]->HandleMasterIncomingPacket(packet);

    ExternalEventHelper helper(aiObjectContext);
    helper.HandlePacket(masterPacketHandlers, packet);
}

void PlayerbotAI::UpdateNextCheckDelay()
{
    int delay = 1;
    
    Group* group = bot->GetGroup();
    if (group) 
        delay += group->GetMembersCount() / 10;
    
    SetNextCheckDelay(delay);
}


void PlayerbotAI::ChangeStrategyIfNecessary()
{
    if (!bot->isAlive())
    {
        ChangeEngine(deadEngine);
        return;
    }

    Unit* target = aiObjectContext->GetValue<Unit*>("current target")->Get();
    if (target && target->isAlive() && target->IsHostileTo(bot))
    {
        ChangeEngine(combatEngine);
    }
    else 
    {
        aiObjectContext->GetValue<Unit*>("current target")->Set(NULL);
        bot->SetSelectionGuid(ObjectGuid());
        ChangeEngine(nonCombatEngine);
    }
}

void PlayerbotAI::ChangeEngine(Engine* engine)
{
    if (currentEngine != engine)
    {
        currentEngine = engine;
        ReInitCurrentEngine();
    }
}

void PlayerbotAI::DoNextAction() 
{
    bot->UpdateUnderwaterState(bot->GetMap(), bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ());
    bot->CheckAreaExploreAndOutdoor();

    AiManagerBase** managers = aiRegistry->GetManagers();
    for (int i=0; i<aiRegistry->GetManagerCount(); i++)
        managers[i]->Update();

    currentEngine->DoNextAction(NULL);

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
        bot->SetSpeedRate(MOVE_FLIGHT, GetMaster()->GetSpeedRate(MOVE_FLIGHT), true);

        bot->SetSpeedRate(MOVE_RUN, 1.0f, true);
        bot->SetSpeedRate(MOVE_RUN, GetMaster()->GetSpeedRate(MOVE_FLIGHT), true);
    }

    if (aiObjectContext->GetValue<bool>("moving", "self target")->Get())
        return;

    LastMovement& movement = aiObjectContext->GetValue<LastMovement&>("last movement")->Get();
    movement.Update(bot);
}

void PlayerbotAI::ReInitCurrentEngine()
{
    aiRegistry->GetSpellManager()->InterruptSpell();
    currentEngine->Init();
    SetNextCheckDelay(0);
}

void PlayerbotAI::ChangeStrategy( const char* names, Engine* e ) 
{
    if (!e)
        return;

    vector<string> splitted = split(names, ',');
    for (vector<string>::iterator i = splitted.begin(); i != splitted.end(); i++)
    {
        const char* name = i->c_str();
        switch (name[0]) 
        {
        case '+':
            e->addStrategy(name+1);
            break;
        case '-':
            e->removeStrategy(name+1);
            break;
        case '~':
            e->toggleStrategy(name+1);
            break;
        case '?':
            TellMaster(e->ListStrategies().c_str());
            break;
        }
    }
}

void PlayerbotAI::DoSpecificAction(const char* name) 
{ 
    if (!combatEngine->ExecuteAction(name) && !nonCombatEngine->ExecuteAction(name))
    {
        ostringstream out;
        out << "I cannot do ";
        out << name;
        TellMaster(out.str().c_str());
        return;
    }
}

bool PlayerbotAI::ContainsStrategy(StrategyType type)
{
    return combatEngine->ContainsStrategy(type) || nonCombatEngine->ContainsStrategy(type);
}

bool PlayerbotAI::IsTank(Player* player)
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

Creature* PlayerbotAI::GetCreature(ObjectGuid guid)
{
    if (!guid)
        return NULL;

    if (bot->GetMapId() != GetMaster()->GetMapId())
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

GameObject* PlayerbotAI::GetGameObject(ObjectGuid guid)
{
    if (!guid)
        return NULL;

    if (bot->GetMapId() != GetMaster()->GetMapId())
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

void PlayerbotAI::TellMaster(const char* text)
{
    WorldPacket data(SMSG_MESSAGECHAT, 1024);
    bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, text, LANG_UNIVERSAL);
    GetMaster()->GetSession()->SendPacket(&data);
    bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);

}

void PlayerbotAI::TellMaster(LogLevel level, const char* text)
{
    LogLevel logLevel = *aiObjectContext->GetValue<LogLevel>("log level");

    if (logLevel < level)
        return;

    ostringstream out;
    out << LogLevelAction::logLevel2string(level) << ": " << text;
    TellMaster(out.str().c_str());
}