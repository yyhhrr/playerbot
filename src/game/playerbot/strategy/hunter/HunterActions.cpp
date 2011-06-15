#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "../GenericActions.h"
#include "HunterActions.h"

using namespace ai;

bool CastSerpentStingAction::isUseful()
{
    return AI_VALUE2(uint8, "health", "current target") > 50;
}

bool CastViperStingAction::isUseful()
{
    return AI_VALUE2(uint8, "mana", "self target") < 50 && AI_VALUE2(uint8, "mana", "current target") >= 30;
}

bool CastArcaneShotAction::isUseful()
{
    return AI_VALUE2(uint8, "health", "current target") >= 5 && AI_VALUE2(uint8, "mana", "self target") >= 30;
}

bool CastExplosiveShotAction::isUseful()
{
    return AI_VALUE2(uint8, "health", "current target") >= 25 && AI_VALUE2(uint8, "mana", "self target") >= 30;
}

bool CastAimedShotAction::isUseful()
{
    return AI_VALUE2(uint8, "health", "current target") >= 5 && AI_VALUE2(uint8, "mana", "self target") >= 30;
}

bool CastAspectOfTheCheetahAction::isUseful() 
{
    return !ai->GetAi()->HasAnyAuraOf(GetTarget(), "aspect of the cheetah", "aspect of the pack", NULL);
}

bool CastAspectOfTheViperAction::isUseful() 
{
	return CastBuffSpellAction::isUseful() && AI_VALUE2(uint8, "mana", "self target") < 50;
}

Value<Unit*>* CastFreezingTrap::GetTargetValue()
{
    return ai->GetAi()->GetAiObjectContext()->GetValue<Unit*>("cc target", "freezing trap");
}
