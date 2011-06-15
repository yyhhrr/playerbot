#include "../../pchdef.h"
#include "../playerbot.h"
#include "GenericActions.h"

using namespace ai;

ChangeCombatStrategyAction::ChangeCombatStrategyAction(PlayerbotAI* ai, const char* name) : Action(ai, "change strategy")
{
    this->name = name;
}

bool ChangeCombatStrategyAction::Execute(Event event)
{
    ai->ChangeCombatStrategy(name.c_str());
    return true;
}
