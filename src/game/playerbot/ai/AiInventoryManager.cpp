#include "../../pchdef.h"
#include "../playerbot.h"

#include "../../GridNotifiers.h"
#include "../../CellImpl.h"
#include "../../GridNotifiersImpl.h"

#include "../strategy/ItemVisitors.h"
#include "../strategy/ItemCountValue.h"

using namespace ai;
using namespace std;

uint32 extractMoney(const string& text);

AiInventoryManager::AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
}

AiInventoryManager::~AiInventoryManager()
{
}









void AiInventoryManager::HandleCommand(const string& text, Player& fromPlayer)
{
	
}

void AiInventoryManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
}

void AiInventoryManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
}


void AiInventoryManager::Query(const string& text)
{
}

