#include "../../pchdef.h"
#include "../playerbot.h"
#include "AttackersValue.h"

using namespace ai;

AttackerMap AttackersValue::Calculate()
{
    Player* bot = ai->GetBot();
    Player* master = ai->GetMaster();

    if (!attackerMapProvider)
        attackerMapProvider = new AttackerMapProvider(master);

    attackerMapProvider->Reset();
    return attackerMapProvider->GetAttackers(); 
}