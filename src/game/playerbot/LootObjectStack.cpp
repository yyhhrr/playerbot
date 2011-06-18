#include "../pchdef.h"
#include "LootObjectStack.h"
#include "playerbot.h"

using namespace ai;
using namespace std;

#define MAX_LOOT_OBJECT_COUNT 10

LootObject::LootObject(Player* bot, ObjectGuid guid)
	: guid(guid)
{
    worldObject = NULL;
    loot = NULL;

	PlayerbotAI* ai = bot->GetPlayerbotAI();

    Creature *creature = ai->GetCreature(guid);
    if (creature && creature->getDeathState() == CORPSE)
    {
        loot = &creature->loot;
        worldObject = creature;
        return;
    }

    GameObject* gameObject = ai->GetGameObject(guid);
    if (gameObject)
    {
        loot = &gameObject->loot;
        worldObject = gameObject;
        return;
    }
}

LootObject::LootObject(const LootObject& other)
{
    worldObject = other.worldObject;
    loot = other.loot;
    guid = other.guid;
}

LootObjectStack::LootObjectStack(Player* bot)
{
    this->bot = bot;
}

void LootObjectStack::Add(ObjectGuid guid)
{
    availableLoot.insert(guid);
    if (availableLoot.size() < MAX_LOOT_OBJECT_COUNT)
        return;

    vector<LootObject> ordered = OrderByDistance();
    for (size_t i = MAX_LOOT_OBJECT_COUNT; i < ordered.size(); i++)
        Remove(ordered[i].guid);
}

void LootObjectStack::Remove(ObjectGuid guid)
{
    availableLoot.erase(availableLoot.find(guid));
}

void LootObjectStack::Clear()
{
    availableLoot.clear();
}

bool LootObjectStack::CanLoot(float maxDistance)
{
    return !OrderByDistance(maxDistance).empty();
}

LootObject LootObjectStack::GetLoot(float maxDistance)
{
    vector<LootObject> ordered = OrderByDistance(maxDistance);
    return ordered.empty() ? LootObject() : *ordered.begin();
}

vector<LootObject> LootObjectStack::OrderByDistance(float maxDistance)
{
    map<float, LootObject> sortedMap;
    set<ObjectGuid> safeCopy(availableLoot);
    for (set<ObjectGuid>::iterator i = safeCopy.begin(); i != safeCopy.end(); i++)
    {
        ObjectGuid guid = *i;
        LootObject lootObject(bot, guid);
        if (lootObject.IsEmpty())
            continue;

        float distance = bot->GetDistance(lootObject.worldObject);
        if (!maxDistance || distance <= maxDistance)
            sortedMap[distance] = lootObject;
    }

    vector<LootObject> result;
    for (map<float, LootObject>::iterator i = sortedMap.begin(); i != sortedMap.end(); i++)
        result.push_back(i->second);
    return result;
}
