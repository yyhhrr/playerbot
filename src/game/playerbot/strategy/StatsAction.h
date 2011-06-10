#pragma once

#include "Action.h"

namespace ai
{
    class StatsAction : public Action {
    public:
        StatsAction(AiManagerRegistry* const ai) : Action(ai, "stats") {}
        virtual bool ExecuteResult();

    private:
        void ListBagSlots(ostringstream &out);
        void ListXP(ostringstream &out);
        void ListRepairCost(ostringstream &out);
        void ListGold(ostringstream &out);
        uint32 EstRepairAll();
        uint32 EstRepair(uint16 pos);

    };

}