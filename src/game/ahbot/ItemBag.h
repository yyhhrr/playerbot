#pragma once;

namespace ahbot
{
    using namespace std;

    class ItemBag 
    {
    public:
        ItemBag();

    public:
        void Init(bool silent = false);
        vector<uint32>& Get(Category* category) { return content[category]; }
        int32 GetCount(Category* category) { return content[category].size(); }
        int32 GetCount(Category* category, uint32 item);
        bool Add(ItemPrototype const* proto);

    protected:
        void Shuffle(vector<uint32>& items);
        virtual void Load() = 0;
        virtual string GetName() = 0;

    protected:
        map<Category*,vector<uint32>> content;
    };

    class AvailableItemsBag : public ItemBag
    {
    public:
        AvailableItemsBag() {}

    protected:
        virtual void Load();
        virtual string GetName() { return "available"; }
    };

    class InAuctionItemsBag : public ItemBag
    {
    public:
        InAuctionItemsBag(uint32 auctionId) : auctionId(auctionId) {}

    protected:
        virtual void Load();
        virtual string GetName();

    private:
        uint32 auctionId;
    };
};