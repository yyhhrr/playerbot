#include "../../pchdef.h"
#include "../playerbot.h"
#include "TradeStatusAction.h"
#include "../PlayerbotAI.h"
#include "ItemVisitors.h"

using namespace ai;


bool compare_items(const ItemPrototype *proto1, const ItemPrototype *proto2)
{
    if (proto1->Class != proto2->Class)
        return proto1->Class > proto2->Class;

    if (proto1->SubClass != proto2->SubClass)
        return proto1->SubClass < proto2->SubClass;

    if (proto1->Quality != proto2->Quality)
        return proto1->Quality < proto2->Quality;

    if (proto1->ItemLevel != proto2->ItemLevel)
        return proto1->ItemLevel > proto2->ItemLevel;

    return false;
}

bool TradeStatusAction::Execute(Event event)
{
    Player* bot = ai->GetAi()->GetBot();

    if (!bot->GetTrader())
        return false;

    WorldPacket p(event.getPacket());
    p.rpos(0);
    uint32 status;
    p >> status;

    if (status == TRADE_STATUS_TRADE_ACCEPT)
    {
        WorldPacket p;
        uint32 status = 0;
        p << status;
        bot->GetSession()->HandleAcceptTradeOpcode(p);
        return true;
    }
    else if (status == TRADE_STATUS_BEGIN_TRADE)
    {
        BeginTrade();
        return true;
    }
    
    return false;
}


void TradeStatusAction::BeginTrade()
{
    Player* bot = ai->GetAi()->GetBot();

    WorldPacket p;
    bot->GetSession()->HandleBeginTradeOpcode(p);

    ListItemsVisitor visitor;
    IterateItems(&visitor);

    list<ItemPrototype const*> items;
    for (map<uint32, int>::iterator i = visitor.items.begin(); i != visitor.items.end(); i++)
    {
        items.push_back(sItemStorage.LookupEntry<ItemPrototype>(i->first));
    }
    items.sort(compare_items);

    uint32 oldClass = -1;
    for (list<ItemPrototype const*>::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *proto = *i;

        if (proto->Class != oldClass)
        {
            oldClass = proto->Class;
            switch (proto->Class)
            {
            case ITEM_CLASS_CONSUMABLE:
                ai->GetAi()->TellMaster("--- consumable ---");
                break;
            case ITEM_CLASS_CONTAINER:
                ai->GetAi()->TellMaster("--- container ---");
                break;
            case ITEM_CLASS_WEAPON:
                ai->GetAi()->TellMaster("--- weapon ---");
                break;
            case ITEM_CLASS_GEM:
                ai->GetAi()->TellMaster("--- gem ---");
                break;
            case ITEM_CLASS_ARMOR:
                ai->GetAi()->TellMaster("--- armor ---");
                break;
            case ITEM_CLASS_REAGENT:
                ai->GetAi()->TellMaster("--- reagent ---");
                break;
            case ITEM_CLASS_PROJECTILE:
                ai->GetAi()->TellMaster("--- projectile ---");
                break;
            case ITEM_CLASS_TRADE_GOODS:
                ai->GetAi()->TellMaster("--- trade goods ---");
                break;
            case ITEM_CLASS_GENERIC:
                ai->GetAi()->TellMaster("--- generic ---");
                break;
            case ITEM_CLASS_RECIPE:
                ai->GetAi()->TellMaster("--- recipe ---");
                break;
            case ITEM_CLASS_MONEY:
                ai->GetAi()->TellMaster("--- money ---");
                break;
            case ITEM_CLASS_QUIVER:
                ai->GetAi()->TellMaster("--- quiver ---");
                break;
            case ITEM_CLASS_QUEST:
                ai->GetAi()->TellMaster("--- quest items ---");
                break;
            case ITEM_CLASS_KEY:
                ai->GetAi()->TellMaster("--- keys ---");
                break;
            case ITEM_CLASS_PERMANENT:
                ai->GetAi()->TellMaster("--- permanent ---");
                break;
            case ITEM_CLASS_MISC:
                ai->GetAi()->TellMaster("--- other ---");
                break;
            case ITEM_CLASS_GLYPH:
                ai->GetAi()->TellMaster("--- glyph ---");
                break;
            }
        }

        TellItem(proto, visitor.items[proto->ItemId]);
    }
}

