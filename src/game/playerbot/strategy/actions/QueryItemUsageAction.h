#pragma once

#include "../Action.h"

namespace ai
{
    class QueryItemUsageAction : public Action {
    public:
        QueryItemUsageAction(PlayerbotAI* ai) : Action(ai, "query item usage") {}
        virtual bool Execute(Event event);

    private:
        void QueryItemsUsage(ItemIds items);
        void QueryItemUsage(ItemPrototype const *item);

    };
}