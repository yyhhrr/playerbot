#include "../../pchdef.h"
#include "../playerbot.h"
#include "TaxiAction.h"
#include "LastMovementValue.h"

using namespace ai;

bool TaxiAction::Execute(Event event)
{
    Player* bot = ai->GetAi()->GetBot();
    AiObjectContext *context = ai->GetAi()->GetAiObjectContext();
    list<Unit*> units = *context->GetValue<list<Unit*>>("nearest npcs");
    for (list<Unit*>::iterator i = units.begin(); i != units.end(); i++)
    {
        Creature *npc = bot->GetNPCIfCanInteractWith((*i)->GetObjectGuid(), UNIT_NPC_FLAG_FLIGHTMASTER);
        if (!npc)
            continue;

        LastMovement& movement = ai->GetAi()->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();
        if (movement.taxiNodes.empty())
        {
            ostringstream out;
            out << "I will order the taxi from " << npc->GetName() << ". Please start flying, then instruct me again";
            TellMaster(out);
            return true;
        }

        if (!bot->ActivateTaxiPathTo(movement.taxiNodes, npc))
        {
            TellMaster("I can not fly with you");
            return false;
        }

        return true;
    }

    TellMaster("Cannot find any flightmaster to talk");
    return false;
}
