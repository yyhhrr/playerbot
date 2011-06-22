#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "SellAction.h"
#include "../ItemVisitors.h"

using namespace ai;

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

    ItemIds ids = chat->parseItems(text);

    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
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
    ObjectGuid vendorguid = master->GetSelectionGuid();
    if (!vendorguid)
    {
        ai->TellMaster("Select a vendor first");
        return;
    }

    ObjectGuid itemguid = item->GetObjectGuid();
    uint32 count = item->GetCount();

    WorldPacket p;
    p << vendorguid << itemguid << count;
    bot->GetSession()->HandleSellItemOpcode(p);

    ostringstream out; out << chat->formatItem(item->GetProto()) << " sold";
    ai->TellMaster(out);
}
