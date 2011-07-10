#pragma once;
#include "Config\Config.h"

using namespace std;

#define MAX_AHBOT_CATEGORIES 8


namespace ahbot
{
    class Category
    {
    public:
        Category() {}

    public:
        virtual bool Contains(ItemPrototype const* proto) = 0;
        virtual string GetName() = 0;

        virtual int32 GetMaxAllowedAuctionCount() 
        {
            ostringstream out; out << "AhBot.MaxAllowedAuctionCount." << GetName();
            return sConfig.GetIntDefault(out.str().c_str(), 15);
        }

        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 1;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            return urand(1, proto->GetMaxStackSize());
        }

        virtual uint32 GetPrice(ItemPrototype const* proto)
        {
            uint32 price = proto->BuyPrice;
            if (!price) price = proto->SellPrice;
            
            if (price)
                return price * (1 + proto->Quality);

            return sConfig.GetIntDefault("AhBot.DefaultMinPrice", 20) * proto->ItemLevel * (1 + proto->Quality);
        }
    };

    class Consumable : public Category
    {
    public:
        Consumable() : Category() {}
        static Consumable instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_CONSUMABLE;
        }

        virtual string GetName() { return "consumable"; }
    
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 10;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            uint32 maxStackSize = proto->GetMaxStackSize();
            if (maxStackSize == 1)
                return 1;

            if (maxStackSize <= 10)
                return urand(1, 10);

            return urand(1, 4) * maxStackSize / 5;
        }
    };

    class Quest : public Category
    {
    public:
        Quest() : Category() {}
        static Quest instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_QUEST;
        }
        virtual string GetName() { return "quest"; }
        
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 5;
        }
    };

    class Trade : public Category
    {
    public:
        Trade() : Category() {}
        static Trade instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_TRADE_GOODS;
        }
        virtual string GetName() { return "trade"; }
        
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 5;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            uint32 maxStack = proto->GetMaxStackSize();
            if (maxStack < 2)
                return maxStack;

            switch (proto->Quality) 
            {
            case ITEM_QUALITY_NORMAL:
                return maxStack;
            case ITEM_QUALITY_UNCOMMON:
                return urand(1, maxStack);
            }

            return 1;
        }
    };

    class Enchant : public Category
    {
    public:
        Enchant() : Category() {}
        static Enchant instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_PERMANENT || 
                proto->Class == ITEM_CLASS_GEM || 
                proto->Class == ITEM_CLASS_GLYPH;
        }
        virtual string GetName() { return "enchant"; }
        
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 5;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            return 1;
        }
    };

    class Reagent : public Category
    {
    public:
        Reagent() : Category() {}
        static Reagent instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_REAGENT;
        }
        virtual string GetName() { return "reagent"; }
    };

    class Recipe : public Category
    {
    public:
        Recipe() : Category() {}
        static Recipe instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_RECIPE;
        }
        virtual string GetName() { return "recipe"; }
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 1;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            return 1;
        }
    };

    class Equip : public Category
    {
    public:
        Equip() : Category() {}
        static Equip instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Class == ITEM_CLASS_WEAPON ||
                proto->Class == ITEM_CLASS_ARMOR || 
                proto->Class == ITEM_CLASS_QUIVER || 
                proto->Class == ITEM_CLASS_CONTAINER;
        }
        virtual string GetName() { return "equip"; }
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 1;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            return 1;
        }
    };

    class Other : public Category
    {
    public:
        Other() : Category() {}
        static Other instance;

    public:
        virtual bool Contains(ItemPrototype const* proto)
        {
            return proto->Quality > ITEM_QUALITY_POOR && (
                proto->Class == ITEM_CLASS_MISC ||
                proto->Class == ITEM_CLASS_GENERIC || 
                proto->Class == ITEM_CLASS_MONEY);
        }
        virtual string GetName() { return "other"; }
        
        virtual int32 GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
        {
            return 1;
        }

        virtual int32 GetStackCount(ItemPrototype const* proto)
        {
            return 1;
        }
    };
};
