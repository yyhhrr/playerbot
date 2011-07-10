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
        AhBot() : nextAICheckTime(0), player(NULL) {}
        virtual ~AhBot();

    public:
        ObjectGuid GetAHBplayerGUID();
        void Init();
        void Update();
        void HandleCommand(string command);
        void Won(AuctionEntry* entry) { AddToHistory(entry, 1); }
        void Expired(AuctionEntry* entry) { /* do nothing */ }

    private:
        void Update(int auction, ItemBag* inAuction);
        void Update(int auction, Category* category, ItemBag* inAuctionItems);
        void Answer(int auction, Category* category, ItemBag* inAuctionItems);
        void AddAuctions(int auction, Category* category, ItemBag* inAuctionItems);
        void AddAuction(int auction, Category* category, ItemPrototype const* proto);
        void Expire(int auction);
        void AddToHistory(AuctionEntry* entry, uint32 won);
        void CleanupHistory();

    private:
        AvailableItemsBag availableItems;
        static uint32 auctionIds[MAX_AUCTIONS];
        WorldSession* session;
        Player* player;
        time_t nextAICheckTime;
    };
};

#define auctionbot MaNGOS::Singleton<ahbot::AhBot>::Instance()
