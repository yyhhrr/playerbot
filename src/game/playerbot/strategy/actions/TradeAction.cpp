#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TradeAction.h"
#include "../ItemVisitors.h"
#include "../values/ItemCountValue.h"

using namespace ai;

uint32 extractMoney(const string& text);
void extractItemIds(const string& text, list<uint32>& itemIds);

bool TradeAction::Execute(Event event)
{
    

    string text = event.getParam();
    uint32 copper = extractMoney(text);
    if (copper > 0)
    {
        WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_GOLD, 4);
        *packet << copper;
        bot->GetSession()->QueuePacket(packet);
    }

    int8 slot = -1;

    uint32 quality = InventoryItemValue::TextToItemQuality(text.c_str());

    if (quality != MAX_ITEM_QUALITY) 
    {
        size_t pos = text.find(" ");
        int count = pos!=string::npos ? atoi(text.substr(pos + 1).c_str()) : TRADE_SLOT_TRADED_COUNT;
        if (count < 1) count = 1;
        else if (count > TRADE_SLOT_TRADED_COUNT) count = TRADE_SLOT_TRADED_COUNT;
        FindItemsToTradeByQualityVisitor visitor(quality, count);
        IterateItems(&visitor);
        list<Item*> found = visitor.GetResult();
        for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
            TradeItem(**i, slot);
        return true;
    }

    list<uint32> ids; /* = */ extractItemIds(text, ids);
    for (list<uint32>::iterator i = ids.begin(); i != ids.end(); i++)
        TradeItem(&FindItemByIdVisitor(*i), slot);

    return true;
}

bool TradeAction::TradeItem(FindItemVisitor *visitor, int8 slot)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item* item = visitor->GetResult();
    if (item) return TradeItem(*item, slot);
    return false;
}

bool TradeAction::TradeItem(const Item& item, int8 slot)
{
    

    if (!bot->GetTrader() || item.IsInTrade())
        return false;

    if (!item.CanBeTraded() && slot != TRADE_SLOT_NONTRADED)
        slot = TRADE_SLOT_NONTRADED;

    int8 tradeSlot = -1;
    Item* itemPtr = const_cast<Item*>(&item);

    TradeData* pTrade = bot->GetTradeData();
    if ((slot >= 0 && slot < TRADE_SLOT_COUNT) && pTrade->GetItem(TradeSlots(slot)) == NULL)
        tradeSlot = slot;

    if (slot == TRADE_SLOT_NONTRADED)
        pTrade->SetItem(TRADE_SLOT_NONTRADED, itemPtr);
    else 
    {
        for (uint8 i = 0; i < TRADE_SLOT_TRADED_COUNT && tradeSlot == -1; i++)
        {
            if (pTrade->GetItem(TradeSlots(i)) == itemPtr)
            {
                tradeSlot = i;

                WorldPacket* const packet = new WorldPacket(CMSG_CLEAR_TRADE_ITEM, 1);
                *packet << (uint8) tradeSlot;
                bot->GetSession()->QueuePacket(packet);
                pTrade->SetItem(TradeSlots(i), NULL);
                return true;
            }
        }

        for (uint8 i = 0; i < TRADE_SLOT_TRADED_COUNT && tradeSlot == -1; i++)
        {
            if (pTrade->GetItem(TradeSlots(i)) == NULL)
            {
                pTrade->SetItem(TradeSlots(i), itemPtr);
                tradeSlot = i;
            }
        }
    }

    if (tradeSlot == -1) return false;

    WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_ITEM, 3);
    *packet << (uint8) tradeSlot << (uint8) item.GetBagSlot()
        << (uint8) item.GetSlot();
    bot->GetSession()->QueuePacket(packet);
    return true;
}

