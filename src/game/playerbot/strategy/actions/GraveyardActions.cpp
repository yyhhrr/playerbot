#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GraveyardActions.h"
#include "../../../MovementGenerator.h"

using namespace ai;

bool RepopAtGraveyardAction::Execute(Event event)
{
    if (bot->isAlive())
        return false;

    bot->GetMotionMaster()->Clear();
    bot->RepopAtGraveyard();
    return true;
}
