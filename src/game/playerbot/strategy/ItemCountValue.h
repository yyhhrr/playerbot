#pragma once
#include "Value.h"
#include "ItemVisitors.h"

namespace ai
{
    class ItemCountValue : public CalculatedValue<uint8>, public Qualified
	{
	public:
        ItemCountValue(AiManagerRegistry* const ai) : CalculatedValue<uint8>(ai) {}

    public:
        virtual uint8 Calculate();
        Item* Find(FindItemVisitor &visitor);
	};

    class InventoryItemValue : public CalculatedValue<Item*>, public Qualified
    {
    public:
        InventoryItemValue(AiManagerRegistry* const ai) : CalculatedValue<Item*>(ai) {}

        virtual Item* Calculate();

        static uint32 TextToItemQuality(const char* text);

    protected:
        Item* Find(FindItemVisitor &visitor);
    };
}
