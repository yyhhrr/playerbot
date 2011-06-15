#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "SellAction.h"
#include "../ItemVisitors.h"

using namespace ai;
void extractItemIds(const string& text, list<uint32>& itemIds);


class SellItemsVisitor : public IterateItemsVisitor
{
public:
    SellItemsVisitor(SellAction* action) : IterateItemsVisitor() 
    {
        this->action = action;
    }

    virtual bool Visit(Item* item)
    {
        action->Sell(item);
        return true;
    }

private:
    SellAction* action;
};

class SellGrayItemsVisitor : public SellItemsVisitor
{
public:
    SellGrayItemsVisitor(SellAction* action) : SellItemsVisitor(action) {}

    virtual bool Visit(Item* item)
    {
        if (item->GetProto()->Quality != ITEM_QUALITY_POOR)
            return true;

        return SellItemsVisitor::Visit(item);
    }
};


bool SellAction::Execute(Event event)
{
    string text = event.getParam();

    if (text == "gray" || text == "*")
    {
        IterateItems(&SellGrayItemsVisitor(this));
        return true;
    }

    list<uint32> ids; /* = */ extractItemIds(text, ids);

    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        Sell(&FindItemByIdVisitor(*i));

    return true;
}


void SellAction::Sell(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item* item = visitor->GetResult();
    if (item) Sell(item);
}

void SellAction::Sell(Item* item)
{
    Player* bot = ai->GetBot();
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
