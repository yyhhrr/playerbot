#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "../GenericActions.h"
#include "HunterActions.h"

using namespace ai;

bool CastSerpentStingAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) > 50;
}

bool CastViperStingAction::isUseful()
{
    return statsManager->GetManaPercent(targetManager->GetSelf()) < 50 &&
		statsManager->GetManaPercent(targetManager->GetCurrentTarget()) >= 30;
}

bool CastArcaneShotAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) >= 5 && statsManager->GetManaPercent(targetManager->GetSelf()) >= 30;
}

bool CastExplosiveShotAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) >= 25 && statsManager->GetManaPercent(targetManager->GetSelf()) >= 30;
}

bool CastAimedShotAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) >= 5 && statsManager->GetManaPercent(targetManager->GetSelf()) >= 30;
}

bool CastAspectOfTheCheetahAction::isUseful() {
    return !spellManager->HasAnyAuraOf(GetTarget(), "aspect of the cheetah", "aspect of the pack", NULL);
}

bool CastAspectOfTheViperAction::isUseful() {
	return CastBuffSpellAction::isUseful() && statsManager->GetManaPercent(targetManager->GetSelf()) < 50;
}

Value<Unit*>* CastFreezingTrap::GetTargetValue()
{
    return ai->GetAi()->GetAiObjectContext()->GetValue<Unit*>("cc target", "freezing trap");
}
