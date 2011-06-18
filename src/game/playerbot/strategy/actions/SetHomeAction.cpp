#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "SetHomeAction.h"


using namespace ai;

bool SetHomeAction::Execute(Event event)
{
    list<Unit*> npcs = AI_VALUE(list<Unit*>, "nearest npcs");
    for (list<Unit*>::iterator i = npcs.begin(); i != npcs.end(); i++)
    {
        Creature *unit = bot->GetNPCIfCanInteractWith((*i)->GetObjectGuid(), UNIT_NPC_FLAG_INNKEEPER);
        if (!unit)
            continue;

        bot->GetSession()->SendBindPoint(unit);
        ai->TellMaster("Home inn set");
        return true;
    }

    ai->TellMaster("Can't find any innkeeper");
    return false;
}
