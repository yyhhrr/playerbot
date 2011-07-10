#include "Category.h"
#include "ItemBag.h"

using namespace ahbot;

int32 Category::GetMaxAllowedAuctionCount() 
{
    ostringstream out; out << "AhBot.MaxAllowedAuctionCount." << GetName();
    return sConfig.GetIntDefault(out.str().c_str(), 15);
}

uint32 Category::GetPrice(ItemPrototype const* proto)
{
    double price = GetDefaultPrice(proto) * (GetCategoryPriceMultiplier() + GetItemPriceMultiplier(proto));
    return (uint32)price;
}

double Category::GetCategoryPriceMultiplier()
{
    double result = 1.0;

    QueryResult* results = CharacterDatabase.PQuery(
        "SELECT COUNT(*), MIN(buytime), MAX(buytime) FROM ahbot_history WHERE category = '%s' AND won = '1'", 
        GetName().c_str());
    if (results)
    {
        Field* fields = results->Fetch();
        uint32 count = fields[0].GetUInt32();

        if (count)
            result = sqrt(GetMultiplier(count, fields[1].GetUInt32(), fields[2].GetUInt32()));

        delete results;
    }

    return result;
}

double Category::GetMultiplier(double count, double firstBuyTime, double lastBuyTime)
{
    double k1 = (double)count / (double)((time(0) - firstBuyTime) / 3600 / 24 + 1);
    double k2 = (double)count / (double)((time(0) - lastBuyTime) / 3600 / 24 + 1);
    return (1.0 + k1 + k2) * sConfig.GetFloatDefault("AhBot.PriceMultiplier", 1.0f);
}

double Category::GetItemPriceMultiplier(ItemPrototype const* proto)
{
    double result = 1.0;

    QueryResult* results = CharacterDatabase.PQuery(
        "SELECT COUNT(*), MIN(buytime), MAX(buytime) FROM ahbot_history WHERE won = '1' AND item = '%u'", 
        proto->ItemId);
    if (results)
    {
        Field* fields = results->Fetch();
        uint32 count = fields[0].GetUInt32();

        if (count)
            result = GetMultiplier(count, fields[1].GetUInt32(), fields[2].GetUInt32());

        delete results;
    }

    return result;
}

uint32 Category::GetDefaultPrice(ItemPrototype const* proto)
{
    uint32 price = proto->BuyPrice;
    if (!price) price = proto->SellPrice;

    if (price)
        return price * (1 + proto->Quality);

    return sConfig.GetIntDefault("AhBot.DefaultMinPrice", 20) * proto->ItemLevel * (1 + proto->Quality);
}
