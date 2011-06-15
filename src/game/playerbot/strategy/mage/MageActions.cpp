#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageActions.h"

using namespace ai;

Value<Unit*>* CastPolymorphAction::GetTargetValue()
{
    return ai->GetAiObjectContext()->GetValue<Unit*>("cc target", getName());
}
