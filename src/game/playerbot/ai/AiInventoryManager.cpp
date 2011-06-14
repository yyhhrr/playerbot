#include "../../pchdef.h"
#include "../playerbot.h"

#include "../../GridNotifiers.h"
#include "../../CellImpl.h"
#include "../../GridNotifiersImpl.h"

#include "../strategy/ItemVisitors.h"

using namespace ai;
using namespace std;

uint32 extractMoney(const string& text);

AiInventoryManager::AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
}

AiInventoryManager::~AiInventoryManager()
{
}


void AiInventoryManager::IterateItems(IterateItemsVisitor* visitor, IterateItemsMask mask)
{
    if (mask & ITERATE_ITEMS_IN_BAGS)
        IterateItemsInBags(visitor);

    if (mask & ITERATE_ITEMS_IN_EQUIP)
        IterateItemsInEquip(visitor);
}

void AiInventoryManager::IterateItemsInBags(IterateItemsVisitor* visitor)
{
    for(int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			if (!visitor->Visit(pItem))
				return;

    for(int i = KEYRING_SLOT_START; i < CURRENCYTOKEN_SLOT_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			if (!visitor->Visit(pItem))
				return;

    for(int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        if (Bag *pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            for(uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
					if (!visitor->Visit(pItem))
						return;
}

void AiInventoryManager::IterateItemsInEquip(IterateItemsVisitor* visitor)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if(!pItem)
            continue;

        if (!visitor->Visit(pItem))
            return;
    }
}


void AiInventoryManager::UseItem(FindItemVisitor* visitor, const uint32 delay)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item* item = visitor->GetResult();
    if (!item) 
        return;
    
    UseItem(*item);
    if (delay) bot->GetPlayerbotAI()->SetNextCheckDelay(delay);
}

bool AiInventoryManager::HasItem(FindItemVisitor* visitor)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    return visitor->GetResult();
}

void AiInventoryManager::UseItem(Item& item)
{
	uint8 bagIndex = item.GetBagSlot();
	uint8 slot = item.GetSlot();
	uint8 cast_count = 1;
	uint32 spellid = 0; // only used in combat
	uint64 item_guid = item.GetGUID();
	uint32 glyphIndex = 0; // ??
	uint8 unk_flags = 0; // not 0x02

	// create target data
	// note other targets are possible but not supported at the moment
	// see SpellCastTargets::read in Spell.cpp to see other options
	// for setting target

    WorldPacket* const packet = new WorldPacket(CMSG_USE_ITEM, 1 + 1 + 1 + 4 + 8 + 4 + 1 + 8 + 1);
    *packet << bagIndex << slot << cast_count << spellid << item_guid
        << glyphIndex << unk_flags;

    for (int i=0; i<MAX_ITEM_PROTO_SPELLS; i++)
    {
        uint32 spellId = item.GetProto()->Spells[i].SpellId;
        if (!spellId)
            continue;

        const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(spellId);
        Item* itemForSpell = aiRegistry->GetSpellManager()->FindItemForSpell(pSpellInfo);
        if (itemForSpell)
        {
            if (itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                continue;

            if (bot->GetTrader())
            {
                *packet << TARGET_FLAG_TRADE_ITEM << (uint8)1 << (uint64)TRADE_SLOT_NONTRADED;
            }
            else
            {
                *packet << TARGET_FLAG_ITEM;
                *packet << itemForSpell->GetPackGUID();
            }
            bot->GetSession()->QueuePacket(packet);
            return;
        }
    }

    *packet << TARGET_FLAG_SELF;
 	bot->GetSession()->QueuePacket(packet);
}

int AiInventoryManager::GetItemCount(const char* name) 
{
    QueryNamedItemCountVisitor visitor(name);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);
    return visitor.GetCount();
}

void AiInventoryManager::extractItemIds(const string& text, list<uint32>& itemIds)
{
	uint8 pos = 0;
	while (true)
	{
		int i = text.find("Hitem:", pos);
		if (i == -1)
			break;
		pos = i + 6;
		int endPos = text.find(':', pos);
		if (endPos == -1)
			break;
		string idC = text.substr(pos, endPos - pos);
		uint32 id = atol(idC.c_str());
		pos = endPos;
		if (id)
			itemIds.push_back(id);
	}
}

void AiInventoryManager::EquipItem(const char* link)
{
	list<uint32> ids; /* = */ extractItemIds(link, ids);
    
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        EquipItem(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::EquipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item *item = visitor->GetResult();
    if (item) EquipItem(*item);
}

void AiInventoryManager::EquipItem(Item& item)
{
	uint8 bagIndex = item.GetBagSlot();
	uint8 slot = item.GetSlot();

	WorldPacket* const packet = new WorldPacket(CMSG_AUTOEQUIP_ITEM, 2);
	*packet << bagIndex << slot;
	bot->GetSession()->QueuePacket(packet);
}


void AiInventoryManager::UnequipItem(const char* link)
{
    list<uint32> ids; /* = */ extractItemIds(link, ids);

    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        UnequipItem(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::UnequipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item *item = visitor->GetResult();
    if (item) UnequipItem(*item);
}

void AiInventoryManager::UnequipItem(Item& item)
{
    uint8 bagIndex = item.GetBagSlot();
    uint8 slot = item.GetSlot();
    uint8 dstBag = NULL_BAG; 

    WorldPacket* const packet = new WorldPacket(CMSG_AUTOSTORE_BAG_ITEM, 3);
    *packet << bagIndex << slot << dstBag;
    bot->GetSession()->QueuePacket(packet);
}

void AiInventoryManager::UseItem(const char* link)
{
    list<uint32> ids; /* = */ extractItemIds(link, ids);
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        UseItem(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::ItemLocalization(string& itemName, const uint32 itemID)
{
	int loc = ai->GetMaster()->GetSession()->GetSessionDbLocaleIndex();
	wstring wnamepart;

	ItemLocale const *pItemInfo = sObjectMgr.GetItemLocale(itemID);
	if (pItemInfo)
	{
		if (pItemInfo->Name.size() > loc && !pItemInfo->Name[loc].empty())
		{
			const string name = pItemInfo->Name[loc];
			if (Utf8FitTo(name, wnamepart))
				itemName = name.c_str();
		}
	}
}

void AiInventoryManager::Buy(const char* link)
{
    list<uint32> itemIds;
    extractItemIds(link, itemIds);
    if (itemIds.empty()) 
        return;

    Player* master = bot->GetPlayerbotAI()->GetMaster();
    uint64 vendorguid = master->GetSelectionGuid().GetRawValue();
    if (!vendorguid)
        return;

    Creature *pCreature = bot->GetNPCIfCanInteractWith(vendorguid,UNIT_NPC_FLAG_VENDOR);
	if (!pCreature)
	{
		ai->TellMaster("Cannot talk to vendor");
		return;
	}

    VendorItemData const* tItems = pCreature->GetVendorTemplateItems();
    for (list<uint32>::iterator i = itemIds.begin(); i != itemIds.end(); i++) 
    {
    	for (uint32 slot = 0; slot < tItems->GetItemCount(); slot++)
    	{
    		if (tItems->GetItem(slot)->item == *i)
    	        bot->BuyItemFromVendorSlot(vendorguid, *i, slot, 1, NULL_BAG, NULL_SLOT);
    	}
    }
}

void AiInventoryManager::Reward(const char* link)
{
	list<uint32> itemIds;
	extractItemIds(link, itemIds);
	if (itemIds.empty()) 
		return;

	uint32 itemId = itemIds.front();
	bool wasRewarded = false;
	const ObjectGuid &questRewarder = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid();
	uint64 questRewarderGUID = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid().GetRawValue();
    bot->SetSelectionGuid(questRewarder);
	Object* pNpc = aiRegistry->GetAi()->GetGameObject(questRewarder);
	if (!pNpc)
		pNpc = ObjectAccessor::GetUnit(*bot, questRewarder);

	if (!pNpc)
		return;

	QuestMenu& questMenu = bot->PlayerTalkClass->GetQuestMenu();
	for (uint32 iI = 0; !wasRewarded && iI < questMenu.MenuItemCount(); ++iI)
	{
		QuestMenuItem const& qItem = questMenu.GetItem(iI);

		uint32 questID = qItem.m_qId;
		Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);
		QuestStatus status = bot->GetQuestStatus(questID);

		// if quest is complete, turn it in
		if (status == QUEST_STATUS_COMPLETE && 
			! bot->GetQuestRewardStatus(questID) && 
			pQuest->GetRewChoiceItemsCount() > 1 &&
			bot->CanRewardQuest(pQuest, false))
		{
			for (uint8 rewardIdx=0; !wasRewarded && rewardIdx < pQuest->GetRewChoiceItemsCount(); ++rewardIdx)
			{
				ItemPrototype const * const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
				if (itemId == pRewardItem->ItemId)
				{
					bot->RewardQuest(pQuest, rewardIdx, pNpc, false);

					string questTitle  = pQuest->GetTitle();
					string itemName = pRewardItem->Name1;
					ItemLocalization(itemName, pRewardItem->ItemId);

					ostringstream out;
					out << "|cffffffff|Hitem:" << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r rewarded";
					ai->TellMaster(out.str().c_str());
					wasRewarded = true;
				}
			}
		}
	}
}

void AiInventoryManager::ListQuestItems()
{
}

void AiInventoryManager::Sell(string link) 
{
    if (link == "gray" || link == "*")
    {
        IterateItems(&SellGrayItemsVisitor(this));
        return;
    }

    list<uint32> ids; /* = */ extractItemIds(link, ids);
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        Sell(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::Sell(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item* item = visitor->GetResult();
    if (item) Sell(item);
}

void AiInventoryManager::Sell(Item* item)
{
    uint64 vendorguid = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid().GetRawValue();
    if (!vendorguid)
    {
        ai->TellMaster("Select a vendor first");
        return;
    }

    uint64 itemguid = item->GetGUID();
    uint32 count = item->GetCount();

    WorldPacket p;
    p << vendorguid << itemguid << count;
    bot->GetSession()->HandleSellItemOpcode(p);
}

void AiInventoryManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text.size() > 2 && text.substr(0, 2) == "u " || text.size() > 4 && text.substr(0, 4) == "use ")
	{
		UseItem(text.c_str());
	}
	else if (text.size() > 2 && text.substr(0, 2) == "e " || text.size() > 6 && text.substr(0, 6) == "equip ")
	{
		EquipItem(text.c_str());
	}
    else if (text.size() > 3 && text.substr(0, 3) == "ue " || text.size() > 6 && text.substr(0, 8) == "unequip ")
    {
        UnequipItem(text.c_str());
    }
	else if (text.size() > 2 && text.substr(0, 2) == "r " || text.size() > 7 && text.substr(0, 7) == "reward ")
	{
		Reward(text.c_str());
	}
    else if (text.size() > 2 && text.substr(0, 2) == "b " || text.size() > 4 && text.substr(0, 4) == "buy ")
    {
        Buy(text.c_str());
    }
    else if (text.size() > 2 && text.substr(0, 2) == "s " || text.size() > 4 && text.substr(0, 5) == "sell ")
    {
        string link = text.substr(text.find(" ") + 1);
        Sell(link.c_str());
    }
    else if (text.size() > 2 && text.substr(0, 2) == "c " || text.size() > 4 && text.substr(0, 6) == "count ")
    {
        ListCount(text.c_str());
    }
    else if (bot->GetTrader() && bot->GetTrader()->GetGUID() == fromPlayer.GetGUID())
    {
        Trade(text.c_str());
    }
	else
	{
		uint32 quality = TextToItemQuality(text.c_str());
		if (quality == MAX_ITEM_QUALITY)
		{
			ListCount(text.c_str());
			return;
		}

		FindItemsToTradeByQualityVisitor visitor(quality, 100);
		IterateItems(&visitor);
		list<Item*> found = visitor.GetResult();
		for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
			TellItem((*i)->GetProto(), (*i)->GetCount());
	}
}

void AiInventoryManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
}

void AiInventoryManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
}


void AiInventoryManager::Query(const string& text)
{
}

void AiInventoryManager::QueryItemCount(ItemPrototype const * item) 
{
    QueryItemCountVisitor visitor(item->ItemId);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);

    int count = visitor.GetCount();
    if (count)
    {
        ostringstream out;
        out << count << "x";
        ai->TellMaster(out.str().c_str());
    }
}

void AiInventoryManager::ListCount(const char* link)
{
    list<uint32> items; /* = */ extractItemIds(link, items);
    for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *item = sItemStorage.LookupEntry<ItemPrototype>(*i);
        QueryItemCount(item);
    }

}


void AiInventoryManager::UseHealingPotion() 
{
    UseItem(&FindPotionVisitor(bot, 441));
}

bool AiInventoryManager::HasHealingPotion() 
{
    return HasItem(&FindPotionVisitor(bot, 441));
}


void AiInventoryManager::UseManaPotion() 
{
    UseItem(&FindPotionVisitor(bot, 438));
}

bool AiInventoryManager::HasManaPotion() 
{
    return HasItem(&FindPotionVisitor(bot, 438));
}


void AiInventoryManager::UsePanicPotion() 
{
}

bool AiInventoryManager::HasPanicPotion() 
{
    return false;
}


void AiInventoryManager::UseFood() 
{
    UseItem(&FindFoodVisitor(bot, 11), 30);
}

bool AiInventoryManager::HasFood() 
{
    return HasItem(&FindFoodVisitor(bot, 11));
}


void AiInventoryManager::UseDrink() 
{
    UseItem(&FindFoodVisitor(bot, 59), 30);
}

bool AiInventoryManager::HasDrink() 
{
    return HasItem(&FindFoodVisitor(bot, 59));
}

void AiInventoryManager::FindAndUse(const char* item, uint8 delay)
{
    UseItem(&FindUsableNamedItemVisitor(bot, item), delay);
}







void AiInventoryManager::Trade(const char* text)
{
    uint32 copper = extractMoney(text);
    if (copper > 0)
    {
        WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_GOLD, 4);
        *packet << copper;
        bot->GetSession()->QueuePacket(packet);
    }

    int8 slot = !strncmp(text, "nt ", 3) ? TRADE_SLOT_NONTRADED : -1;

	uint32 quality = TextToItemQuality(text);

	if (quality != MAX_ITEM_QUALITY) 
	{
		const char* pos = strchr(text, ' ');
		int count = pos ? atoi(pos + 1) : TRADE_SLOT_TRADED_COUNT;
		if (count < 1) count = 1;
		else if (count > TRADE_SLOT_TRADED_COUNT) count = TRADE_SLOT_TRADED_COUNT;
		FindItemsToTradeByQualityVisitor visitor(quality, count);
		IterateItems(&visitor);
		list<Item*> found = visitor.GetResult();
		for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
			TradeItem(**i, slot);
		return;
	}

    list<uint32> ids; /* = */ extractItemIds(text, ids);
    for (list<uint32>::iterator i = ids.begin(); i != ids.end(); i++)
        TradeItem(&FindItemByIdVisitor(*i), slot);
}

bool AiInventoryManager::TradeItem(FindItemVisitor *visitor, int8 slot)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item* item = visitor->GetResult();
    if (item) return TradeItem(*item, slot);
    return false;
}

bool AiInventoryManager::TradeItem(const Item& item, int8 slot)
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

uint32 AiInventoryManager::TextToItemQuality( const char* text ) 
{
	uint32 quality = MAX_ITEM_QUALITY;

	if (strstr(text, "poor") || strstr(text, "gray"))
		quality = ITEM_QUALITY_POOR;
	else if (strstr(text, "normal") || strstr(text, "white"))
		quality = ITEM_QUALITY_NORMAL;
	else if (strstr(text, "uncommon") || strstr(text, "green"))
		quality = ITEM_QUALITY_UNCOMMON;
	else if (strstr(text, "rare") || strstr(text, "blue"))
		quality = ITEM_QUALITY_RARE;
	else if (strstr(text, "epic") || strstr(text, "violet"))
		quality = ITEM_QUALITY_EPIC;
	
	return quality;
}

void AiInventoryManager::TellItem(ItemPrototype const * proto, int count) 
{
	ostringstream out;

	char color[32];
	sprintf(color, "%x", ItemQualityColors[proto->Quality]);

	out << " |c" << color << "|Hitem:" << proto->ItemId
		<< ":0:0:0:0:0:0:0" << "|h[" << proto->Name1
		<< "]|h|r";
	if (count > 1)
		out << "x" << count;

	ai->TellMaster(out.str().c_str());
}
