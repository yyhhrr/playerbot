#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AttackersValue.h"

using namespace ai;

AttackerMap AttackersValue::Calculate()
{
    
    

    if (!attackerMapProvider)
        attackerMapProvider = new AttackerMapProvider(master);

    attackerMapProvider->Reset();
    return attackerMapProvider->GetAttackers(); 
}