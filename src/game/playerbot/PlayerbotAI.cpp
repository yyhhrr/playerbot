#include "../pchdef.h"
#include "playerbot.h"

#include "strategy/ExternalEventHelper.h"
#include "ai/AiFactory.h"

#include "../GridNotifiers.h"
#include "../GridNotifiersImpl.h"
#include "../CellImpl.h"

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

PlayerbotAI::PlayerbotAI() : PlayerbotAIBase()
{
	aiRegistry = NULL;
    aiObjectContext = NULL;
    combatEngine = NULL;
    nonCombatEngine = NULL;
    currentEngine = NULL;
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

    currentEngine = nonCombatEngine;

    packetHandlers[CMSG_GOSSIP_HELLO] = "gossip hello";
    packetHandlers[SMSG_GROUP_INVITE] = "group invite";
    packetHandlers[SMSG_GROUP_SET_LEADER] = "group set leader";
    packetHandlers[BUY_ERR_NOT_ENOUGHT_MONEY] = "not enough money";
    packetHandlers[BUY_ERR_REPUTATION_REQUIRE] = "not enough reputation";

    packetHandlers[CMSG_GAMEOBJ_USE] = "use game object";
    packetHandlers[CMSG_GAMEOBJ_REPORT_USE] = "use game object";
    packetHandlers[CMSG_QUESTGIVER_HELLO] = "gossip hello";
    packetHandlers[CMSG_QUESTGIVER_COMPLETE_QUEST] = "complete quest";
    packetHandlers[CMSG_QUESTGIVER_ACCEPT_QUEST] = "accept quest";
    packetHandlers[SMSG_QUESTGIVER_QUEST_DETAILS] = "quest share";

    packetHandlers[CMSG_LOOT_ROLL] = "loot roll";
}

PlayerbotAI::~PlayerbotAI()
{
    if (combatEngine) 
        delete combatEngine;

    if (nonCombatEngine) 
        delete nonCombatEngine;

    if (aiObjectContext)
        delete aiObjectContext;

	if (aiRegistry)
		delete aiRegistry;
}

void PlayerbotAI::UpdateAI(uint32 elapsed)
{
	if (bot->isAlive())
		ChangeStrategyIfNecessary();

	if (!CanUpdateAI() || bot->IsBeingTeleported())
		return;

	if (bot->isAlive())
		DoNextAction();
	else
		aiRegistry->GetMoveManager()->Resurrect();

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

	if (fromPlayer.GetGuildId() != bot->GetGuildId())
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
}

void PlayerbotAI::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    AiManagerBase** managers = aiRegistry->GetManagers();
    for (int i=0; i<aiRegistry->GetManagerCount(); i++)
        managers[i]->HandleMasterIncomingPacket(packet);

    ExternalEventHelper helper(aiObjectContext);
    helper.HandlePacket(packetHandlers, packet);
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
    Unit* target = aiObjectContext->GetValue<Unit*>("current target")->Get();
    if (target && !bot->isInFrontInMap(target, BOT_REACT_DISTANCE))
    {
        bot->SetFacingTo(bot->GetAngle(target));
    }

    if (target && target->isAlive() && target->IsHostileTo(bot))
    {
        if (currentEngine != combatEngine)
        {
            currentEngine = combatEngine;
            ReInitCurrentEngine();
        }
    }
    else 
    {
        aiObjectContext->GetValue<Unit*>("current target")->Set(NULL);
        bot->SetSelectionGuid(ObjectGuid());
        if (currentEngine != nonCombatEngine)
        {
            currentEngine = nonCombatEngine;
            ReInitCurrentEngine();
        }
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
            aiRegistry->GetSocialManager()->TellMaster(e->ListStrategies().c_str());
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
        aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
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
