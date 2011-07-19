#include "../pchdef.h"
#include "LootObjectStack.h"
#include "playerbot.h"

using namespace ai;
using namespace std;

#define MAX_LOOT_OBJECT_COUNT 10

LootTarget::LootTarget(ObjectGuid guid) : guid(guid), asOfTime(time(0))
{
}

LootTarget::LootTarget(LootTarget& other)
{
    guid = other.guid;
    asOfTime = other.asOfTime;
}

LootTarget& LootTarget::operator=(LootTarget const& other)
{
    if((void*)this == (void*)&other)
        return *this;

    guid = other.guid;
    asOfTime = other.asOfTime;

    return *this;
}

bool LootTarget::operator< (const LootTarget& other) const
{
    return guid < other.guid;
}

void LootTargetList::shrink(time_t fromTime)
{
    for (set<LootTarget>::iterator i = begin(); i != end(); )
    {
        if (i->asOfTime <= fromTime)
            erase(i++);
		else
			++i;
    }
}

LootObject::LootObject(Player* bot, ObjectGuid guid)
	: guid(guid), skillId(SKILL_NONE), reqSkillValue(0), reqItem(NULL)
{
	PlayerbotAI* ai = bot->GetPlayerbotAI();

    Creature *creature = ai->GetCreature(guid);
    if (creature && creature->getDeathState() == CORPSE)
    {
        if (!creature->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE) && !creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            return;

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

WorldObject* LootObject::GetWorldObject(Player* bot)
{
    PlayerbotAI* ai = bot->GetPlayerbotAI();

    Creature *creature = ai->GetCreature(guid);
    if (creature && creature->getDeathState() == CORPSE)
        return creature;

    GameObject* go = ai->GetGameObject(guid);
    if (go && go->isSpawned())
        return go;

    return NULL;
}

LootObject::LootObject(const LootObject& other)
{
    guid = other.guid;
    skillId = other.skillId;
    reqSkillValue = other.reqSkillValue;
    reqItem = other.reqItem;
}

bool LootObject::IsLootPossible(Player* bot)
{
    if (IsEmpty() || !GetWorldObject(bot))
        return false;

    PlayerbotAI* ai = bot->GetPlayerbotAI();

    if (reqItem && !bot->HasItemCount(reqItem, 1))
        return false;

    if (skillId == SKILL_NONE)
        return true;

    if (skillId == SKILL_FISHING)
        return false;

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
    alreadyLooted.clear();
}

bool LootObjectStack::CanLoot(float maxDistance)
{
    vector<LootObject> ordered = OrderByDistance(maxDistance);
    for (vector<LootObject>::iterator i = ordered.begin(); i != ordered.end(); i++)
    {
        LootObject result = *i;
        if (alreadyLooted.find(result.guid) == alreadyLooted.end())
            return true;
    }

    return false;
}

LootObject LootObjectStack::GetLoot(float maxDistance)
{
    vector<LootObject> ordered = OrderByDistance(maxDistance);
    for (vector<LootObject>::iterator i = ordered.begin(); i != ordered.end(); i++)
    {
        LootObject result = *i;
        if (alreadyLooted.insert(result.guid).second)
            return result;
    }

    return LootObject();
}

vector<LootObject> LootObjectStack::OrderByDistance(float maxDistance)
{
    alreadyLooted.shrink(time(0) - 10);
    availableLoot.shrink(time(0) - 30);

    map<float, LootObject> sortedMap;
    LootTargetList safeCopy(availableLoot);
    for (LootTargetList::iterator i = safeCopy.begin(); i != safeCopy.end(); i++)
    {
        ObjectGuid guid = i->guid;
        LootObject lootObject(bot, guid);
        if (!lootObject.IsLootPossible(bot))
            continue;

        float distance = bot->GetDistance(lootObject.GetWorldObject(bot));
        if (!maxDistance || distance <= maxDistance)
            sortedMap[distance] = lootObject;
    }

    vector<LootObject> result;
    for (map<float, LootObject>::iterator i = sortedMap.begin(); i != sortedMap.end(); i++)
        result.push_back(i->second);
    return result;
}

