#include "../../pchdef.h"
#include "../playerbot.h"
#include "GenericActions.h"

using namespace ai;

ChangeCombatStrategyAction::ChangeCombatStrategyAction(AiManagerRegistry* const ai, const char* name) : Action(ai, "change strategy")
{
    this->name = name;
}

bool ChangeCombatStrategyAction::Execute(Event event)
{
    ai->GetAi()->ChangeCombatStrategy(name.c_str());
    return true;
}

bool UseItemAction::isUseful()
{
    return ai->GetSpellManager()->IsSpellCastUseful(getName(), AI_VALUE(Unit*, "self target"));
}