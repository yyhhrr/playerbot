#pragma once

using namespace std;

namespace ai 
{
    enum LootStrategy 
    {
        LOOTSTRATEGY_QUEST = 1,
        LOOTSTRATEGY_SKILL = 2,
        LOOTSTRATEGY_GRAY = 3,
        LOOTSTRATEGY_NORMAL = 4,
        LOOTSTRATEGY_ALL = 5
    };

    class LootObject
    {
    public:
        LootObject() {}
        LootObject(Player* bot, ObjectGuid guid);
        LootObject(const LootObject& other);

    public:
        bool IsEmpty() { return !guid || (time_t() - time) > 30; }
        bool IsLootPossible(Player* bot);
        WorldObject* GetWorldObject(Player* bot);
        ObjectGuid guid;
        time_t time;

        uint32 skillId;
        uint32 reqSkillValue;
        uint32 reqItem;
    };

    class LootObjectStack
    {
    public:
        LootObjectStack(Player* bot) : bot(bot) {}

    public:
        void Add(ObjectGuid guid);
        void Remove(ObjectGuid guid);
        void Clear();
        bool CanLoot(float maxDistance);
        LootObject GetLoot(float maxDistance = 0);

    private:
        vector<LootObject> OrderByDistance(float maxDistance = 0);

    private:
        Player* bot;
        set<ObjectGuid> availableLoot;
    };

};