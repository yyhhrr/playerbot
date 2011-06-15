#include "../../pchdef.h"
#include "../playerbot.h"
#include "TellLosAction.h"
#include "../PlayerbotAI.h"

using namespace ai;

bool TellLosAction::Execute(Event event)
{
    Player* bot = ai->GetBot();
    AiObjectContext *context = ai->GetAiObjectContext();

    string &param = event.getParam();

    if (param.empty() || param == "targets")
    {
        list<Unit*> targets = *context->GetValue<list<Unit*>>("possible targets");
        ListUnits("--- Targets ---", targets);
    }
    
    if (param.empty() || param == "npcs")
    {
        list<Unit*> npcs = *context->GetValue<list<Unit*>>("nearest npcs");
        ListUnits("--- NPCs ---", npcs);
    }
    
    if (param.empty() || param == "corpses")
    {
        list<Unit*> corpses = *context->GetValue<list<Unit*>>("nearest corpses");
        ListUnits("--- Corpses ---", corpses);
    }
    
    if (param.empty() || param == "gos" || param == "game objects")
    {
        list<GameObject*> gos = *context->GetValue<list<GameObject*>>("nearest game objects");
        ListGameObjects("--- Game objects ---", gos);
    }

    return true;
}

void TellLosAction::ListUnits(const char* title, list<Unit*> units)
{
    ai->TellMaster(title);

    for (list<Unit*>::iterator i = units.begin(); i != units.end(); i++)
        ai->TellMaster((*i)->GetName());

}
void TellLosAction::ListGameObjects(const char* title, list<GameObject*> gos)
{
    ai->TellMaster(title);

    for (list<GameObject*>::iterator i = gos.begin(); i != gos.end(); i++)
        ai->TellMaster((*i)->GetGOInfo()->name);
}
