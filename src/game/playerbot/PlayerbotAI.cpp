#include "../pchdef.h"
#include "playerbot.h"

#include "strategy/ExternalEventHelper.h"
#include "ai/AiFactory.h"

#include "../GridNotifiers.h"
#include "../GridNotifiersImpl.h"
#include "../CellImpl.h"
#include "strategy/LastMovementValue.h"
#include "strategy/LogLevelAction.h"
#include "strategy/LastSpellCastValue.h"

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

uint64 extractGuid(WorldPacket& packet)
{
    uint8 mask;
    packet >> mask;
    uint64 guid = 0;
    uint8 bit = 0;
    uint8 testMask = 1;
    while (true)
    {
        if (mask & testMask)
        {
            uint8 word;
            packet >> word;
            guid += (word << bit);
        }
        if (bit == 7)
            break;
        ++bit;
        testMask <<= 1;
    }
    return guid;
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
    case SMSG_SPELL_FAILURE:
        {
            WorldPacket p(packet);
            uint64 casterGuid = extractGuid(p);
            if (casterGuid != bot->GetGUID())
                return;
            uint8  castCount;
            uint32 spellId;
            p >> castCount;
            p >> spellId;
            SpellInterrupted(spellId);
            return;
        }

    case SMSG_SPELL_GO:
        {
            WorldPacket p(packet);
            uint64 casterGuid = extractGuid(p);
            if (casterGuid != bot->GetGUID())
                return;
            WaitForSpellCast();
            return;
        }
    case SMSG_SPELL_DELAYED:
        {
            WorldPacket p(packet);
            uint64 casterGuid = extractGuid(p);
            if (casterGuid != bot->GetGUID())
                return;
            IncreaseNextCheckDelay(1);
        }
    }
}


void PlayerbotAI::WaitForSpellCast()
{
    uint32 lastSpellId = aiObjectContext->GetValue<LastSpellCast&>("last spell id")->Get().id;
    Spell* const pSpell = bot->FindCurrentSpellBySpellId(lastSpellId);
    if (!pSpell)
        return;

    if (pSpell->IsChannelActive())
        SetNextCheckDelay(GetSpellDuration(pSpell->m_spellInfo) / 1000);
}


void PlayerbotAI::SpellInterrupted(uint32 spellid)
{
    LastSpellCast& lastSpell = aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get();
    if (lastSpell.id != spellid)
        return;

    int castTimeSpent = time(0) - lastSpell.time;

    int32 globalCooldown = CalculateGlobalCooldown(lastSpell.id);
    if (castTimeSpent < globalCooldown)
        SetNextCheckDelay(globalCooldown - castTimeSpent);
    else
        SetNextCheckDelay(1);

    lastSpell.Reset();
}

int32 PlayerbotAI::CalculateGlobalCooldown(uint32 spellid)
{
    if (!spellid) 
        return 0;

    SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );

    if (!spellInfo || 
        spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_1 || 
        spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_2 || 
        spellInfo->Attributes & SPELL_ATTR_OUTDOORS_ONLY ||
        spellInfo->Attributes & SPELL_ATTR_DISABLED_WHILE_ACTIVE ||
        !spellInfo->StartRecoveryCategory)
        return 0;

    if (spellInfo->AttributesEx3 & SPELL_ATTR_EX3_REQ_WAND)
        return GLOBAL_COOLDOWN;

    return GLOBAL_COOLDOWN;
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
    InterruptSpell();
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
        return HasAnyAuraOf(player, "bear form", "dire bear form");
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


bool PlayerbotAI::HasAura(const char* name, Unit* player) 
{
    return HasAura(aiObjectContext->GetValue<uint32>("spell id", name)->Get(), player);
}

bool PlayerbotAI::HasAura(uint32 spellId, const Unit* player) 
{
    if (!spellId || !player) 
        return false;

    Unit* unit = (Unit*)player;
    if (unit->GetAura(spellId, EFFECT_INDEX_0) ||
        unit->GetAura(spellId, EFFECT_INDEX_1) ||
        unit->GetAura(spellId, EFFECT_INDEX_2))
        return true;
    return false;
}

bool PlayerbotAI::HasAnyAuraOf(Unit* player, ...)
{
    if (!player)
        return false;

    va_list vl;
    va_start(vl, player);

    const char* cur = NULL;
    do {
        cur = va_arg(vl, const char*);
        if (cur && HasAura(cur, player)) {
            va_end(vl);
            return true;
        }
    }
    while (cur);

    va_end(vl);
    return false;
}

bool PlayerbotAI::CanCastSpell(const char* name, Unit* target)
{
    return CanCastSpell(aiObjectContext->GetValue<uint32>("spell id", name)->Get(), target);
}

bool PlayerbotAI::CanCastSpell(uint32 spellid, Unit* target)
{
    if (!spellid)
        return false;

    if (!target)
        target = bot;

    if (!bot->HasSpell(spellid) || bot->HasSpellCooldown(spellid))
        return false;

    bool positiveSpell = IsPositiveSpell(spellid);
    if (positiveSpell && bot->IsHostileTo(target))
        return false;

    if (!positiveSpell && bot->IsFriendlyTo(target))
        return false;

    SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
    if (!spellInfo)
        return false;

    ObjectGuid oldSel = bot->GetSelectionGuid();
    bot->SetSelectionGuid(target->GetObjectGuid());
    Spell *spell = new Spell(bot, spellInfo, false );
    SpellCastTargets targets;
    targets.setUnitTarget(target);
    spell->m_CastItem = aiObjectContext->GetValue<Item*>("item for spell", spellid)->Get();
    targets.setItemTarget(spell->m_CastItem);
    SpellCastResult result = spell->CheckCast(false);
    delete spell;
    bot->SetSelectionGuid(oldSel);

    switch (result)
    {
    case SPELL_FAILED_TOO_CLOSE:
    case SPELL_FAILED_NOT_BEHIND:
    case SPELL_FAILED_NOT_INFRONT:
    case SPELL_FAILED_NOT_STANDING:
    case SPELL_FAILED_UNIT_NOT_BEHIND:
    case SPELL_FAILED_UNIT_NOT_INFRONT:
    case SPELL_FAILED_OUT_OF_RANGE:
    case SPELL_FAILED_SUCCESS:
    case SPELL_FAILED_LINE_OF_SIGHT:
    case SPELL_FAILED_MOVING:
    case SPELL_FAILED_ONLY_STEALTHED:
    case SPELL_FAILED_ONLY_SHAPESHIFT:
    case SPELL_FAILED_SPELL_IN_PROGRESS:
    case SPELL_FAILED_TRY_AGAIN:
    case SPELL_FAILED_NOT_ON_STEALTHED:
    case SPELL_FAILED_NOT_ON_SHAPESHIFT:
    case SPELL_FAILED_NOT_IDLE:
    case SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW:
    case SPELL_FAILED_SUMMON_PENDING:
    case SPELL_FAILED_BAD_IMPLICIT_TARGETS:
    case SPELL_FAILED_BAD_TARGETS:
    case SPELL_CAST_OK:
    case SPELL_FAILED_ITEM_NOT_FOUND:
        return true;
    default:
        return false;
    }
}


bool PlayerbotAI::CastSpell(const char* name, Unit* target) 
{
    return CastSpell(aiObjectContext->GetValue<uint32>("spell id", name)->Get(), target);
}

bool PlayerbotAI::CastSpell(uint32 spellId, Unit* target)
{
    if (!spellId)
        return false;

    if (!target)
        target = bot;

    if (!bot->isInFrontInMap(target, 10))
        bot->SetInFront(target);

    aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get().Set(spellId, target->GetObjectGuid(), time(0));
    aiObjectContext->GetValue<LastMovement&>("last movement")->Get().Set(NULL);

    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    bot->clearUnitState( UNIT_STAT_CHASE );
    bot->clearUnitState( UNIT_STAT_FOLLOW );

    if (!bot->IsStandState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(spellId);
    ObjectGuid oldSel = bot->GetSelectionGuid().GetRawValue();
    bot->SetSelectionGuid(target->GetObjectGuid());

    Spell *spell = new Spell(bot, pSpellInfo, false);
    SpellCastTargets targets;
    targets.setUnitTarget(target);
    spell->m_CastItem = aiObjectContext->GetValue<Item*>("item for spell", spellId)->Get();
    targets.setItemTarget(spell->m_CastItem);
    spell->prepare(&targets, false);

    bot->SetSelectionGuid(oldSel);

    float castTime = GetSpellCastTime(pSpellInfo);

    if (pSpellInfo->AttributesEx & SPELL_ATTR_EX_CHANNELED_1 ||
        pSpellInfo->AttributesEx & SPELL_ATTR_EX_CHANNELED_2)
        castTime += GetSpellDuration(pSpellInfo);

    castTime = ceil(castTime / 1000.0);

    uint32 globalCooldown = CalculateGlobalCooldown(spellId);
    if (castTime < globalCooldown)
        castTime = globalCooldown;

    SetNextCheckDelay(castTime);
    return true;
}

void PlayerbotAI::InterruptSpell()
{
    WorldPacket* const packet = new WorldPacket(CMSG_CANCEL_CAST, 5);
    LastSpellCast& lastSpell = aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get();
    *packet << lastSpell.id;
    *packet << lastSpell.target;
    bot->GetSession()->QueuePacket(packet);

    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_MAX_SPELL; type++)
        bot->InterruptSpell((CurrentSpellTypes)type);

    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_MAX_SPELL; type++)
        bot->GetMover()->InterruptSpell((CurrentSpellTypes)type);

    SpellInterrupted(lastSpell.id);
}


void PlayerbotAI::RemoveAura(const char* name)
{
    uint32 spellid = aiObjectContext->GetValue<uint32>("spell id", name)->Get();
    if (spellid && HasAura(spellid, bot))
        bot->RemoveAurasDueToSpell(spellid);
}

bool PlayerbotAI::IsSpellCasting(Unit* player)
{
    return player->IsNonMeleeSpellCasted(true);
}

bool PlayerbotAI::HasAuraToDispel(Unit* target, uint32 dispelType) 
{
    for (uint32 type = SPELL_AURA_NONE; type < TOTAL_AURAS; ++type)
    {
        Unit::AuraList auras = target->GetAurasByType((AuraType)type);
        for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
        {
            Aura* aura = *itr;
            const SpellEntry* entry = aura->GetSpellProto();
            uint32 spellId = entry->Id;

            bool isPositiveSpell = IsPositiveSpell(spellId);
            if (bot->IsFriendlyTo(target) && isPositiveSpell)
                continue;

            if (bot->IsHostileTo(target) && !isPositiveSpell)
                continue;

            if (canDispel(entry, dispelType))
                return true;
        }
    }
    return false;
}

#ifndef WIN32
int strcmpi(const char *s1, const char *s2)
{
    for (; *s1 && *s2 && (toupper(*s1) == toupper(*s2)); ++s1, ++s2);
    return *s1 - *s2;
}
#endif

bool PlayerbotAI::canDispel(const SpellEntry* entry, uint32 dispelType) 
{
    if (entry->Dispel == dispelType) {
        return !entry->SpellName[0] ||
            (strcmpi((const char*)entry->SpellName[0], "demon skin") &&
            strcmpi((const char*)entry->SpellName[0], "mage armor") &&
            strcmpi((const char*)entry->SpellName[0], "frost armor") &&
            strcmpi((const char*)entry->SpellName[0], "ice armor"));
    }
    return false;
}

