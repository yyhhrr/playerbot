#pragma once;
#include "Config\Config.h"
#include "Category.h"

using namespace std;

namespace ahbot
{
    class Alchemy : public Consumable
    {
    public:
        Alchemy() : Consumable() {}
        static Alchemy instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Consumable::Contains(proto) &&
                    (proto->SubClass == ITEM_SUBCLASS_POTION ||
                    proto->SubClass == ITEM_SUBCLASS_ELIXIR ||
                    proto->SubClass == ITEM_SUBCLASS_FLASK);
        }

        virtual string GetName() { return "Alchemy"; }
    };

    class Enchants : public Consumable
    {
    public:
        Enchants() : Consumable() {}
        static Enchants instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Consumable::Contains(proto) &&
                    (proto->SubClass == ITEM_SUBCLASS_SCROLL ||
                    proto->SubClass == ITEM_SUBCLASS_ITEM_ENHANCEMENT);
        }

        virtual string GetName() { return "Enchants"; }
    };

    class Food : public Consumable
    {
    public:
        Food() : Consumable() {}
        static Food instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Consumable::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_FOOD;
        }

        virtual string GetName() { return "Food"; }
    };

    class OtherConsumable : public Consumable
    {
    public:
        OtherConsumable() : Consumable() {}
        static OtherConsumable instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Consumable::Contains(proto) &&
                    proto->SubClass != ITEM_SUBCLASS_FOOD &&
                    proto->SubClass != ITEM_SUBCLASS_SCROLL &&
                    proto->SubClass != ITEM_SUBCLASS_ITEM_ENHANCEMENT &&
                    proto->SubClass != ITEM_SUBCLASS_POTION &&
                    proto->SubClass != ITEM_SUBCLASS_ELIXIR &&
                    proto->SubClass != ITEM_SUBCLASS_FLASK;
        }

        virtual string GetName() { return "OtherConsumable"; }
    };
};
