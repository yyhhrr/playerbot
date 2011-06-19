#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AddLootAction.h"

#include "../../LootObjectStack.h"

using namespace ai;

bool AddLootAction::Execute(Event event)
{
    ObjectGuid guid = event.getObject();
    if (!guid)
        return false;

    AI_VALUE(LootObjectStack*, "available loot")->Add(guid);    
    return true;
}

bool AddAllLootAction::Execute(Event event)
{
    list<GameObject*> gos = *context->GetValue<list<GameObject*>>("nearest game objects");
    for (list<GameObject*>::iterator i = gos.begin(); i != gos.end(); i++)
    {
        GameObject* go = *i;
        uint32 type = go->GetGOInfo()->type;

        if (type != GAMEOBJECT_TYPE_CHEST && type != GAMEOBJECT_TYPE_GOOBER)
            continue;

        AI_VALUE(LootObjectStack*, "available loot")->Add(go->GetObjectGuid());
    }

    list<Unit*> corpses = *context->GetValue<list<Unit*>>("nearest corpses");
    for (list<Unit*>::iterator i = corpses.begin(); i != corpses.end(); i++)
        AI_VALUE(LootObjectStack*, "available loot")->Add((*i)->GetObjectGuid());

    return true;
}
