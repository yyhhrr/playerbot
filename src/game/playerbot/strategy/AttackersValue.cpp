#include "../../pchdef.h"
#include "../playerbot.h"
#include "AttackersValue.h"

using namespace ai;

AttackerMap AttackersValue::Calculate()
{
    Player* bot = ai->GetAi()->GetBot();
    Player* master = ai->GetAi()->GetMaster();

    if (!attackerMapProvider)
        attackerMapProvider = new AttackerMapProvider(master);

    attackerMapProvider->Reset();
    return attackerMapProvider->GetAttackers(); 
}