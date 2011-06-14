#include "../../pchdef.h"
#include "../playerbot.h"
#include "ItemCountValue.h"
#include "ItemVisitors.h"

using namespace ai;

uint8 ItemCountValue::Calculate()
{
    QueryNamedItemCountVisitor visitor(qualifier.c_str());
    ai->GetInventoryManager()->IterateItems(&visitor, ITERATE_ALL_ITEMS);
    return visitor.GetCount();
}

