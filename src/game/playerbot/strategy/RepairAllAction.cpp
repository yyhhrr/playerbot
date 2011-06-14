#include "../../pchdef.h"
#include "../playerbot.h"
#include "RepairAllAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool RepairAllAction::Execute(Event event)
{
    Player* bot = ai->GetAi()->GetBot();

    list<Unit*> npcs = AI_VALUE(list<Unit*>, "nearest npcs");
    for (list<Unit*>::iterator i = npcs.begin(); i != npcs.end(); i++)
    {
        Creature *unit = bot->GetNPCIfCanInteractWith((*i)->GetObjectGuid(), UNIT_NPC_FLAG_REPAIR);
        if (!unit)
            continue;
    
        if(bot->hasUnitState(UNIT_STAT_DIED))
            bot->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH);

        float discountMod = bot->GetReputationPriceDiscount(unit);

        uint32 totalCost = bot->DurabilityRepairAll(true, discountMod, false);
        ostringstream out;
        out << "Repaired at " << unit->GetName() << ". Cost " << totalCost;
        ai->GetAi()->TellMaster(out);
        return true;
    }
    
    ai->GetAi()->TellMaster("Cannot find any npc to repair at");
    return false;
}
