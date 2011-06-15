#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockActions.h"

using namespace ai;

Value<Unit*>* CastBanishAction::GetTargetValue()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("cc target", getName());
}
