#pragma once;
#include "Config\Config.h"
#include "Category.h"

using namespace std;

namespace ahbot
{
    class Cloth : public Trade
    {
    public:
        Cloth() : Trade() {}
        static Cloth instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_CLOTH;
        }

        virtual string GetName() { return "Cloth"; }
    };

    class Leather : public Trade
    {
    public:
        Leather() : Trade() {}
        static Leather instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_LEATHER;
        }

        virtual string GetName() { return "Leather"; }
    };

    class Herb : public Trade
    {
    public:
        Herb() : Trade() {}
        static Herb instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_HERB;
        }

        virtual string GetName() { return "Herb"; }
    };

    class Meat : public Trade
    {
    public:
        Meat() : Trade() {}
        static Meat instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_MEAT;
        }

        virtual string GetName() { return "Meat"; }
    };

    class Metal : public Trade
    {
    public:
        Metal() : Trade() {}
        static Metal instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_METAL_STONE;
        }

        virtual string GetName() { return "Metal"; }
    };

    class Disenchants : public Trade
    {
    public:
        Disenchants() : Trade() {}
        static Disenchants instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass == ITEM_SUBCLASS_ENCHANTING;
        }

        virtual string GetName() { return "Disenchants"; }
    };

    class Engineering : public Trade
    {
    public:
        Engineering() : Trade() {}
        static Engineering instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    (proto->SubClass == ITEM_SUBCLASS_PARTS ||
                    proto->SubClass == ITEM_SUBCLASS_DEVICES ||
                    proto->SubClass == ITEM_SUBCLASS_MATERIAL ||
                    proto->SubClass == ITEM_SUBCLASS_EXPLOSIVES);
        }

        virtual string GetName() { return "Engineering"; }
    };

    class OtherTrade : public Trade
    {
    public:
        OtherTrade() : Trade() {}
        static OtherTrade instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return Trade::Contains(proto) &&
                    proto->SubClass != ITEM_SUBCLASS_PARTS &&
                    proto->SubClass != ITEM_SUBCLASS_DEVICES &&
                    proto->SubClass != ITEM_SUBCLASS_MATERIAL &&
                    proto->SubClass != ITEM_SUBCLASS_EXPLOSIVES &&
                    proto->SubClass != ITEM_SUBCLASS_ENCHANTING &&
                    proto->SubClass != ITEM_SUBCLASS_METAL_STONE &&
                    proto->SubClass != ITEM_SUBCLASS_MEAT &&
                    proto->SubClass != ITEM_SUBCLASS_HERB &&
                    proto->SubClass != ITEM_SUBCLASS_LEATHER &&
                    proto->SubClass != ITEM_SUBCLASS_CLOTH;
        }

        virtual string GetName() { return "OtherTrade"; }
    };
};
