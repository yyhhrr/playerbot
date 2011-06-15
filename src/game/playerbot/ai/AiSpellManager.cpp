#include "../../pchdef.h"
#include "../playerbot.h"
#include "../strategy/LastMovementValue.h"
#include "../../MovementGenerator.h"
#include "../strategy/LastSpellCastValue.h"

using namespace ai;
using namespace std;

typedef pair<uint32, uint8> spellEffectPair;
typedef multimap<spellEffectPair, Aura*> AuraMap;

AiSpellManager::AiSpellManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
}

void AiSpellManager::HandleCommand(const string& text, Player& fromPlayer)
{
	
}

void AiSpellManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
}
