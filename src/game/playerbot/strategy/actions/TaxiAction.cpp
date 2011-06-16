#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TaxiAction.h"
#include "../values/LastMovementValue.h"

using namespace ai;

bool TaxiAction::Execute(Event event)
{
    
    
    list<Unit*> units = *context->GetValue<list<Unit*>>("nearest npcs");
    for (list<Unit*>::iterator i = units.begin(); i != units.end(); i++)
    {
        Creature *npc = bot->GetNPCIfCanInteractWith((*i)->GetObjectGuid(), UNIT_NPC_FLAG_FLIGHTMASTER);
        if (!npc)
            continue;

        LastMovement& movement = context->GetValue<LastMovement&>("last movement")->Get();
        if (movement.taxiNodes.empty())
        {
            ostringstream out;
            out << "I will order the taxi from " << npc->GetName() << ". Please start flying, then instruct me again";
            ai->TellMaster(out);
            return true;
        }

        if (!bot->ActivateTaxiPathTo(movement.taxiNodes, npc))
        {
            ai->TellMaster("I can not fly with you");
            return false;
        }

        return true;
    }

    ai->TellMaster("Cannot find any flightmaster to talk");
    return false;
}
