#pragma once

#include "../Action.h"
#include "../ItemVisitors.h"

namespace ai
{
   

    class InventoryAction : public Action {
    public:
        InventoryAction(PlayerbotAI* ai, const char* name) : Action(ai, name) {}

    protected:
        void IterateItems(IterateItemsVisitor* visitor, IterateItemsMask mask = ITERATE_ITEMS_IN_BAGS);        
        void TellItem(ItemPrototype const * proto, int count);

    private:
        void IterateItemsInBags(IterateItemsVisitor* visitor);
        void IterateItemsInEquip(IterateItemsVisitor* visitor);
    };
}