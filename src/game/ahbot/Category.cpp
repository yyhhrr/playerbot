#include "Category.h"
#include "ItemBag.h"
#include "AhBotConfig.h"
#include "PricingStrategy.h"

using namespace ahbot;

int32 Category::GetStackCount(ItemPrototype const* proto)
{
    if (proto->Quality > ITEM_QUALITY_UNCOMMON)
        return 1;

    return urand(1, proto->GetMaxStackSize());
}

int32 Category::GetMaxAllowedItemAuctionCount(ItemPrototype const* proto)
{
    return 1;
}

int32 Category::GetMaxAllowedAuctionCount()
{
    return sAhBotConfig.GetMaxAllowedAuctionCount(GetName());
}

PricingStrategy* Category::GetPricingStrategy()
{
    if (pricingStrategy)
        return pricingStrategy;

    ostringstream out; out << "AhBot.PricingStrategy." << GetName();
    string name = sAhBotConfig.GetStringDefault(out.str().c_str(), "default");
    return pricingStrategy = PricingStrategyFactory::Create(name, this);
}
