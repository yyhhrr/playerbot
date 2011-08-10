#pragma once
#include "../Value.h"
#include "../ItemVisitors.h"
#include "../actions/InventoryAction.h"

namespace ai
{
    class ItemCountValue : public CalculatedValue<uint8>, public Qualified, InventoryAction
	{
	public:
        ItemCountValue(PlayerbotAI* ai) : CalculatedValue<uint8>(ai), InventoryAction(ai, "empty") {}

    public:
        virtual uint8 Calculate();
        Item* Find(FindItemVisitor &visitor);
        virtual bool Execute(Event event) { return false; }
	};

    class InventoryItemValue : public CalculatedValue<list<Item*> >, public Qualified, InventoryAction
    {
    public:
        InventoryItemValue(PlayerbotAI* ai) : CalculatedValue<list<Item*> >(ai), InventoryAction(ai, "empty") {}

        virtual list<Item*> Calculate();

        virtual bool Execute(Event event) { return false; }

    protected:
        Item* Find(FindItemVisitor &visitor);
    };
}
