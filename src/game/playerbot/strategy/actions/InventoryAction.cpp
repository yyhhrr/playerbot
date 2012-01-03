#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "InventoryAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;


class FindPotionVisitor : public FindUsableItemVisitor
{
public:
    FindPotionVisitor(Player* bot, uint32 effectId) : FindUsableItemVisitor(bot), effectId(effectId) {}

    virtual bool Accept(const ItemPrototype* proto)
    {
        if (proto->Class == ITEM_CLASS_CONSUMABLE &&
            proto->SubClass == ITEM_SUBCLASS_POTION &&
            proto->Spells[0].SpellCategory == 4)
        {
            for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
            {
                const SpellEntry* const spellInfo = sSpellStore.LookupEntry(proto->Spells[j].SpellId);
                if (!spellInfo)
                    return false;

                for (int i = 0 ; i < 3; i++)
                {
                    if (spellInfo->Effect[i] == effectId)
                        return true;
                }
            }
        }
        return false;
    }

private:
    uint32 effectId;
};

class FindFoodVisitor : public FindUsableItemVisitor
{
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

void InventoryAction::IterateItems(IterateItemsVisitor* visitor, IterateItemsMask mask)
{
    if (mask & ITERATE_ITEMS_IN_BAGS)
        IterateItemsInBags(visitor);

    if (mask & ITERATE_ITEMS_IN_EQUIP)
        IterateItemsInEquip(visitor);
}

void InventoryAction::IterateItemsInBags(IterateItemsVisitor* visitor)
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

void InventoryAction::IterateItemsInEquip(IterateItemsVisitor* visitor)
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


void InventoryAction::TellItem(ItemPrototype const * proto, int count)
{
    ai->TellMaster(chat->formatItem(proto, count));
}

list<Item*> InventoryAction::parseItems(string text)
{
    list<Item*> found;
    size_t pos = text.find(" ");
    int count = pos!=string::npos ? atoi(text.substr(pos + 1).c_str()) : TRADE_SLOT_TRADED_COUNT;
    if (count < 1) count = 1;
    else if (count > TRADE_SLOT_TRADED_COUNT) count = TRADE_SLOT_TRADED_COUNT;

    if (text == "food")
    {
        FindFoodVisitor visitor(bot, 11);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        Item* item = visitor.GetResult();
        if (item)
            found.push_back(item);
    }

    if (text == "drink")
    {
        FindFoodVisitor visitor(bot, 59);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        Item* item = visitor.GetResult();
        if (item)
            found.push_back(item);
    }

    if (text == "mana potion")
    {
        FindPotionVisitor visitor(bot, SPELL_EFFECT_ENERGIZE);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        Item* item = visitor.GetResult();
        if (item)
            found.push_back(item);
    }

    if (text == "healing potion")
    {
        FindPotionVisitor visitor(bot, SPELL_EFFECT_HEAL);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        Item* item = visitor.GetResult();
        if (item)
            found.push_back(item);
    }

    uint32 quality = chat->parseItemQuality(text);
    if (quality != MAX_ITEM_QUALITY)
    {
        FindItemsToTradeByQualityVisitor visitor(quality, count);
        IterateItems(&visitor);
        found = visitor.GetResult();
    }

    uint32 itemClass = MAX_ITEM_CLASS, itemSubClass = 0;
    if (chat->parseItemClass(text, &itemClass, &itemSubClass))
    {
        FindItemsToTradeByClassVisitor visitor(itemClass, itemSubClass, count);
        IterateItems(&visitor);
        found = visitor.GetResult();
    }

    uint32 fromSlot = chat->parseSlot(text);
    if (fromSlot != EQUIPMENT_SLOT_END)
    {
        Item* item = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, fromSlot);
        if (item)
            found.push_back(item);
    }

    ItemIds ids = chat->parseItems(text);
    for (ItemIds::iterator i = ids.begin(); i != ids.end(); i++)
    {
        FindItemByIdVisitor visitor(*i);
        IterateItems(&visitor, ITERATE_ALL_ITEMS);
        Item* item = visitor.GetResult();
        if (item)
            found.push_back(item);
    }

    return found;
}
