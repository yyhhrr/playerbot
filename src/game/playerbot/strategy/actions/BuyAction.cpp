#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "BuyAction.h"
#include "../ItemVisitors.h"
#include "../values/ItemCountValue.h"

using namespace ai;

uint32 extractMoney(const string& text);
void extractItemIds(const string& text, list<uint32>& itemIds);

bool BuyAction::Execute(Event event)
{
    

    string link = event.getParam().c_str();

    list<uint32> itemIds;
    extractItemIds(link, itemIds);
    if (itemIds.empty()) 
        return false;

    Player* master = bot->GetPlayerbotAI()->GetMaster();
    ObjectGuid vendorguid = master->GetSelectionGuid();
    if (!vendorguid)
        return false;

    Creature *pCreature = bot->GetNPCIfCanInteractWith(vendorguid,UNIT_NPC_FLAG_VENDOR);
    if (!pCreature)
    {
        ai->TellMaster("Cannot talk to vendor");
        return false;
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
    return true;
}
