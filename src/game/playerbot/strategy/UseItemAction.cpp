#include "../../pchdef.h"
#include "../playerbot.h"
#include "UseItemAction.h"

using namespace ai;

bool UseItemAction::Execute(Event event)
{
    string name = event.getParam();
    if (name.empty())
        name = getName();

    Item* item = AI_VALUE2(Item*, "inventory item", name.c_str());
    if (!item)
    {
        ai->GetAi()->TellMaster("Item not found");
        return false;
    }

    UseItem(*item);
    if (name == "food" || name == "drink")
    {
        ai->GetAi()->SetNextCheckDelay(30);
        ai->GetAi()->TellMaster("I will eat/drink for 30 sec");
    }

    return true;
}

void UseItemAction::UseItem(Item& item)
{
    Player* bot = ai->GetAi()->GetBot();
    uint8 bagIndex = item.GetBagSlot();
    uint8 slot = item.GetSlot();
    uint8 cast_count = 1;
    uint32 spellid = 0;
    uint64 item_guid = item.GetGUID();
    uint32 glyphIndex = 0;
    uint8 unk_flags = 0; 

    WorldPacket* const packet = new WorldPacket(CMSG_USE_ITEM, 1 + 1 + 1 + 4 + 8 + 4 + 1 + 8 + 1);
    *packet << bagIndex << slot << cast_count << spellid << item_guid
        << glyphIndex << unk_flags;

    for (int i=0; i<MAX_ITEM_PROTO_SPELLS; i++)
    {
        uint32 spellId = item.GetProto()->Spells[i].SpellId;
        if (!spellId)
            continue;

        Item* itemForSpell = AI_VALUE2(Item*, "item for spell", spellId);
        if (!itemForSpell)
            continue;
        
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

    *packet << TARGET_FLAG_SELF;
    bot->GetSession()->QueuePacket(packet);
}

bool UseItemAction::isPossible() 
{
    return !strcmp(getName(), "use") || AI_VALUE2(uint8, "item count", getName()) > 0;
}

bool UseSpellItemAction::isUseful()
{
    return AI_VALUE2(bool, "spell cast useful", getName());
}
