#include "../pchdef.h"
#include "playerbot.h"

#include "strategy/ExternalEventHelper.h"
#include "ai/AiFactory.h"

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

PlayerbotAI::PlayerbotAI(PlayerbotMgr* mgr, Player* bot) : PlayerbotAIBase()
{
	this->mgr = mgr;
	this->bot = bot;
    aiRegistry = new AiManagerRegistry(this);

    aiObjectContext = AiFactory::createAiObjectContext(bot, aiRegistry);

    combatEngine = AiFactory::createCombatEngine(bot, aiRegistry, aiObjectContext);
    nonCombatEngine = AiFactory::createNonCombatEngine(bot, aiRegistry, aiObjectContext);

    currentEngine = nonCombatEngine;

    packetHandlers[CMSG_GOSSIP_HELLO] = "gossip hello";
    packetHandlers[SMSG_GROUP_INVITE] = "group invite";
    packetHandlers[SMSG_GROUP_SET_LEADER] = "group set leader";
    packetHandlers[BUY_ERR_NOT_ENOUGHT_MONEY] = "not enough money";
    packetHandlers[BUY_ERR_REPUTATION_REQUIRE] = "not enough reputation";
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

    if (text.size() > 2 && text.substr(0, 2) == "q ")
    {
        string query = text.substr(text.find(" ") + 1);
        for (int i=0; i<aiRegistry->GetManagerCount(); i++)
            managers[i]->Query(query);
        return;
    }
    else if (text.size() > 2 && text.substr(0, 2) == "d " || text.size() > 3 && text.substr(0, 3) == "do ")
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
    Unit* target = aiRegistry->GetTargetManager()->GetCurrentTarget();
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
        aiRegistry->GetTargetManager()->SetCurrentTarget(NULL);
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

