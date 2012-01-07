#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ItemForSpellValue.h"

using namespace ai;

Item* ItemForSpellValue::Calculate()
{
    uint32 spellid = atoi(qualifier.c_str());
    if (!spellid)
        return NULL;

    SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
    if (!spellInfo)
        return NULL;

    Player* trader = bot->GetTrader();
    if (trader)
        return trader->GetTradeData()->GetItem(TRADE_SLOT_NONTRADED);

    for( uint8 slot=EQUIPMENT_SLOT_START; slot<EQUIPMENT_SLOT_END; slot++ ) {
        Item* const itemForSpell = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, slot );
        if (!itemForSpell || itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
            continue;

        if (itemForSpell->IsFitToSpellRequirements(spellInfo))
            return itemForSpell;
    }
    return NULL;
}
