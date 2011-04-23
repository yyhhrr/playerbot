#pragma once

using namespace std;

namespace ai 
{
    class LootObject
    {
    public:
        LootObject() {}
        LootObject(Player* bot, ObjectGuid guid);
        LootObject(const LootObject& other);

    public:
        bool IsEmpty() { return !worldObject || !loot; }
        WorldObject* worldObject;
        Loot* loot;
        ObjectGuid guid;
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