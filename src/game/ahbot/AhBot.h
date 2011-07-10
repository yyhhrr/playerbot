#pragma once;

#include "Category.h"
#include "ItemBag.h"
#include "..\playerbot\PlayerbotAIBase.h"

#define MAX_AUCTIONS 3

namespace ahbot
{
    using namespace std;

    class AhBot
    {
    public:
        AhBot() : nextAICheckTime(0) {}

    public:
        ObjectGuid GetAHBplayerGUID();
        void Init();
        void Update();
        void HandleCommand(string command);

    private:
        void Update(int auction, ItemBag* inAuction);
        void Update(int auction, Category* category, ItemBag* inAuctionItems);
        void Answer(int auction, Category* category, ItemBag* inAuctionItems);
        void AddAuctions(int auction, Category* category, ItemBag* inAuctionItems);
        void AddAuction(int auction, Category* category, ItemPrototype const* proto);
        void Expire(int auction);

    private:
        AvailableItemsBag availableItems;
        static uint32 auctionIds[MAX_AUCTIONS];
        Player* player;
        time_t nextAICheckTime;
    };
};

#define auctionbot MaNGOS::Singleton<ahbot::AhBot>::Instance()
