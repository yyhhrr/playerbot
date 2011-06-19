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
        bool IsEmpty() { return !worldObject || !loot || (time_t() - time) > 60; }
        WorldObject* worldObject;
        Loot* loot;
        ObjectGuid guid;
        time_t time;
    };

    class LootObjectStack
    {
    public:
        LootObjectStack(Player* bot);

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