#include "../../pchdef.h"
#include "../playerbot.h"

#include "../../GridNotifiers.h"
#include "../../GridNotifiersImpl.h"
#include "../../CellImpl.h"

using namespace ai;
using namespace std;

void AiTargetManager::HandleCommand(const string& text, Player& fromPlayer)
{
    if (text == "reset")
    {
    }
}

void AiTargetManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{

}


