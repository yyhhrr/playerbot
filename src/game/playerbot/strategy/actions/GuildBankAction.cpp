#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "GuildBankAction.h"

#include "../values/ItemCountValue.h"

using namespace std;
using namespace ai;

bool GuildBankAction::Execute(Event event)
{
    string text = event.getParam();
    if (text.empty())
        return false;

    list<GameObject*> gos = AI_VALUE(list<GameObject*>, "nearest game objects");
    for (list<GameObject*>::iterator i = gos.begin(); i != gos.end(); i++)
    {
        GameObject* go = *i;
        if (!bot->GetGameObjectIfCanInteractWith(go->GetObjectGuid(), GAMEOBJECT_TYPE_GUILD_BANK))
            continue;

        return Execute(text, go);
    }

    ai->TellMaster("Cannot find the guild bank nearby");
    return false;
}

bool GuildBankAction::Execute(string text, GameObject* bank)
{
    bool toChar = text.substr(0, 1) == "-";
    bool result = true;

    ItemIds ids = chat->parseItems(text);
    for (ItemIds::iterator i = ids.begin(); i != ids.end(); i++)
    {
        uint32 itemId = *i;
        result &= Execute(itemId, toChar, bank);
    }

    return result;
}

bool GuildBankAction::Execute(uint32 itemId, bool toChar, GameObject* bank)
{
    Item* item = bot->GetItemByEntry(itemId);
    if (!item)
        return false;

    uint32 playerSlot = item->GetSlot();
    uint32 playerBag = item->GetBagSlot();

    Guild* guild = sGuildMgr.GetGuildById(bot->GetGuildId());
    guild->MoveFromCharToBank(bot, playerBag, playerSlot, 0, INVENTORY_SLOT_BAG_0, 0);

    return true;
}
