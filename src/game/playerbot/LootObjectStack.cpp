#include "../pchdef.h"
#include "LootObjectStack.h"
#include "playerbot.h"

using namespace ai;
using namespace std;

#define MAX_LOOT_OBJECT_COUNT 10

LootObject::LootObject(Player* bot, ObjectGuid guid)
	: guid(guid), skillId(SKILL_NONE), reqSkillValue(0), reqItem(NULL)
{
    worldObject = NULL;
    loot = NULL;
    time = time_t();

	PlayerbotAI* ai = bot->GetPlayerbotAI();

    Creature *creature = ai->GetCreature(guid);
    if (creature && creature->getDeathState() == CORPSE)
    {
        if (!creature->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE) && !creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            return;

        loot = &creature->loot;
        worldObject = creature;
        if (creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
        {
            skillId = creature->GetCreatureInfo()->GetRequiredLootSkill();
            uint32 targetLevel = creature->getLevel();
            reqSkillValue = targetLevel < 10 ? 0 : targetLevel < 20 ? (targetLevel - 10) * 10 : targetLevel * 5;
        }
        return;
    }

    GameObject* go = ai->GetGameObject(guid);
    if (go && go->isSpawned())
    {
        loot = &go->loot;
        worldObject = go;

        uint32 lockId = go->GetGOInfo()->GetLockId();        
        LockEntry const *lockInfo = sLockStore.LookupEntry(lockId);
        if (!lockInfo)
            return;
        
        for (int i = 0; i < 8; ++i)
        {
            switch (lockInfo->Type[i])
            {
            case LOCK_KEY_ITEM:
                if (lockInfo->Index[i] > 0)
                    reqItem = lockInfo->Index[i];
                break;
            case LOCK_KEY_SKILL:
                if (SkillByLockType(LockType(lockInfo->Index[i])) > 0)
                {
                    skillId = SkillByLockType(LockType(lockInfo->Index[i]));
                    reqSkillValue = lockInfo->Skill[i];
                }
                break;
            default:
                break;
            }
        }
    }
}

LootObject::LootObject(const LootObject& other)
{
    worldObject = other.worldObject;
    loot = other.loot;
    guid = other.guid;
    time = other.time;
    skillId = other.skillId;
    reqSkillValue = other.reqSkillValue;
    reqItem = other.reqItem;
}

bool LootObject::IsLootPossible(Player* bot)
{
    if (IsEmpty())
        return false;

    PlayerbotAI* ai = bot->GetPlayerbotAI();

    if (reqItem && !bot->HasItemCount(reqItem, 1))
        return false;

    if (skillId == SKILL_NONE)
        return true;

    if (!bot->HasSkill(skillId))
        return false;

    if (!reqSkillValue)
        return true;

    uint32 skillValue = uint32(bot->GetPureSkillValue(skillId));
    if (reqSkillValue > skillValue)
        return false;

    if (skillId == SKILL_MINING && !bot->HasItemTotemCategory(TC_MINING_PICK))
        return false;

    if (skillId == SKILL_SKINNING && !bot->HasItemTotemCategory(TC_SKINNING_KNIFE))
        return false;

    return true;
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
        if (!lootObject.IsLootPossible(bot))
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

