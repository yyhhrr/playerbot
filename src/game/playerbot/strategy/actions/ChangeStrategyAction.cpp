#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ChangeStrategyAction.h"

using namespace ai;

bool ChangeCombatStrategyAction::Execute(Event event)
{
    string text = event.getParam();
    ai->ChangeCombatStrategy(text.empty() ? getName() : text.c_str());
    return true;
}

bool ChangeNonCombatStrategyAction::Execute(Event event)
{
    string text = event.getParam();
    ai->ChangeNonCombatStrategy(text.c_str());
    return true;
}
