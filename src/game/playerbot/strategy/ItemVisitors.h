#pragma once

char * strstri (const char * str1, const char * str2);

namespace ai
{
    class IterateItemsVisitor 
    {
    public:
        IterateItemsVisitor() {}

        virtual bool Visit(Item* item) = 0;
    };

    class FindItemVisitor : public IterateItemsVisitor {
    public:
        FindItemVisitor() : IterateItemsVisitor(), result(NULL) {}

        virtual bool Visit(Item* item)
        {
            if (!Accept(item->GetProto()))
                return true;

            result = item;
            return false;
        }

        Item* GetResult() { return result; }

    protected:
        virtual bool Accept(const ItemPrototype* proto) = 0;

    private:
        Item* result;
    };

    enum IterateItemsMask
    {
        ITERATE_ITEMS_IN_BAGS = 1,
        ITERATE_ITEMS_IN_EQUIP = 2,
        ITERATE_ALL_ITEMS = 255
    };

    class FindUsableItemVisitor : public FindItemVisitor {
    public:
        FindUsableItemVisitor(Player* bot) : FindItemVisitor() 
        {
            this->bot = bot;
        }

        virtual bool Visit(Item* item)
        {
            if (bot->CanUseItem(item->GetProto()) == EQUIP_ERR_OK)
                return FindItemVisitor::Visit(item);

            return true;
        }

    private:
        Player* bot;
    };


    class FindItemsByQualityVisitor : public IterateItemsVisitor
    {
    public:
        FindItemsByQualityVisitor(uint32 quality, int count) : IterateItemsVisitor() 
        {
            this->quality = quality;
            this->count = count;
        }

        virtual bool Visit(Item* item)
        {
            if (item->GetProto()->Quality != quality)
                return true;

            if (result.size() >= (size_t)count)
                return false;

            result.push_back(item);
            return true;
        }

        list<Item*> GetResult() 
        {
            return result;
        }

    private:
        uint32 quality;
        int count;
        list<Item*> result;
    };

    class FindItemsToTradeByQualityVisitor : public FindItemsByQualityVisitor
    {
    public:
        FindItemsToTradeByQualityVisitor(uint32 quality, int count) : FindItemsByQualityVisitor(quality, count) {}

        virtual bool Visit(Item* item)
        {
            if (item->IsSoulBound())
                return true;

            return FindItemsByQualityVisitor::Visit(item);
        }
    };

    class QueryItemCountVisitor : public IterateItemsVisitor 
    {
    public:
        QueryItemCountVisitor(uint32 itemId) 
        {
            count = 0;
            this->itemId = itemId;
        }

        virtual bool Visit(Item* item)
        {
            if (item->GetProto()->ItemId == itemId)
                count += item->GetCount();

            return true;
        }

        int GetCount() { return count; }

    protected:
        int count;
        uint32 itemId;
    };


    class QueryNamedItemCountVisitor : public QueryItemCountVisitor 
    {
    public:
        QueryNamedItemCountVisitor(const char* name) : QueryItemCountVisitor(0)
        {
            this->name = name;
        }

        virtual bool Visit(Item* item)
        {
            const ItemPrototype* proto = item->GetProto();
            if (proto && proto->Name1 && strstri(proto->Name1, name))
                count += item->GetCount();

            return true;
        }

    private:
        const char* name;
    };



    class FindPotionVisitor : public FindUsableItemVisitor {
    public:
        FindPotionVisitor(Player* bot, uint32 spellId) : FindUsableItemVisitor(bot) 
        {
            this->spellId = spellId;
        }

        virtual bool Accept(const ItemPrototype* proto)
        {
            return proto->Class == ITEM_CLASS_CONSUMABLE && 
                proto->SubClass == ITEM_SUBCLASS_POTION &&    
                proto->Spells[0].SpellCategory == 4 && 
                proto->Spells[0].SpellId == spellId;
        }

    private:
        uint32 spellId;
    };

    class FindFoodVisitor : public FindUsableItemVisitor {
    public:
        FindFoodVisitor(Player* bot, uint32 spellCategory) : FindUsableItemVisitor(bot) 
        {
            this->spellCategory = spellCategory;
        }

        virtual bool Accept(const ItemPrototype* proto)
        {
            return proto->Class == ITEM_CLASS_CONSUMABLE && 
                proto->SubClass == ITEM_SUBCLASS_FOOD && 
                proto->Spells[0].SpellCategory == spellCategory;
        }

    private:
        uint32 spellCategory;
    };


    class FindUsableNamedItemVisitor : public FindUsableItemVisitor {
    public:
        FindUsableNamedItemVisitor(Player* bot, const char* name) : FindUsableItemVisitor(bot) 
        {
            this->name = name;
        }

        virtual bool Accept(const ItemPrototype* proto)
        {
            return proto && proto->Name1 && strstri(proto->Name1, name);
        }

    private:
        const char* name;
    };

    class FindItemByIdVisitor : public FindItemVisitor {
    public:
        FindItemByIdVisitor(uint32 id) : FindItemVisitor() 
        {
            this->id = id;
        }

        virtual bool Accept(const ItemPrototype* proto)
        {
            return proto->ItemId == id;
        }

    private:
        uint32 id;
    };

    class ListItemsVisitor : public IterateItemsVisitor
    {
    public:
        ListItemsVisitor() : IterateItemsVisitor() {}

        map<uint32, int> items;

        virtual bool Visit(Item* item)
        {
            uint32 id = item->GetProto()->ItemId;

            if (items.find(id) == items.end())
                items[id] = 0;

            items[id] += item->GetCount();
            return true;
        }
    };   
}