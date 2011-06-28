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
    bool added = false;

    list<GameObject*> gos = *context->GetValue<list<GameObject*>>("nearest game objects");
    for (list<GameObject*>::iterator i = gos.begin(); i != gos.end(); i++)
        added |= AddLoot((*i)->GetObjectGuid());

    list<Unit*> corpses = *context->GetValue<list<Unit*>>("nearest corpses");
    for (list<Unit*>::iterator i = corpses.begin(); i != corpses.end(); i++)
        added |= AddLoot((*i)->GetObjectGuid());

    return added;
}

bool AddAllLootAction::AddLoot(ObjectGuid guid)
{
    AI_VALUE(LootObjectStack*, "available loot")->Add(guid);
    return true;
}

bool AddGatheringLootAction::AddLoot(ObjectGuid guid)
{
    LootObject loot(bot, guid);

    if (loot.IsEmpty() || !loot.GetWorldObject(bot))
        return false;

    if (loot.skillId == SKILL_NONE)
        return false;

    if (!loot.IsLootPossible(bot))
        return false;

    AddAllLootAction::AddLoot(guid);
    return true;
}
