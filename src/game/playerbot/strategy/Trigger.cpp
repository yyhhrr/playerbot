#include "../../pchdef.h"
#include "../playerbot.h"
#include "Trigger.h"
#include "Action.h"

using namespace ai;

Event Trigger::Check()
{
    return IsActive() ? Event(getName()) : Event();
}

Value<Unit*>* Trigger::GetTargetValue()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>(GetTargetName());
}

Unit* Trigger::GetTarget()
{
    return GetTargetValue()->Get();
}
