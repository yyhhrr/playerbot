#include "Category.h"
#include "ItemBag.h"

using namespace ahbot;

int32 Category::GetMaxAllowedAuctionCount() 
{
    ostringstream out; out << "AhBot.MaxAllowedAuctionCount." << GetName();
    return sConfig.GetIntDefault(out.str().c_str(), 15);
}

double Category::GetStaticItemPriceMultiplier(ItemPrototype const* proto)
{
    ostringstream out; out << "AhBot.PriceMultiplier." << GetName();
    return sConfig.GetFloatDefault(out.str().c_str(), 1.0f);
}

uint32 Category::GetPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    uint32 now = time(0);
    double price = GetStaticItemPriceMultiplier(proto) * 
        GetRarityPriceMultiplier(proto) *
        GetDefaultPrice(proto) * 
        (GetCategoryPriceMultiplier(now, auctionHouse) + GetItemPriceMultiplier(proto, now, auctionHouse));
    return (uint32)price;
}

uint32 Category::GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    uint32 untilTime = time(0) - 3600 * 36;
    double price = GetStaticItemPriceMultiplier(proto) * 
        GetRarityPriceMultiplier(proto) *
        GetDefaultPrice(proto) * 
        (GetCategoryPriceMultiplier(untilTime, auctionHouse) + GetItemPriceMultiplier(proto, untilTime, auctionHouse));
    return (uint32)price;
}

double Category::GetRarityPriceMultiplier(ItemPrototype const* proto)
{
    double result = 1.0;

    uint32 i = proto->ItemId;
    QueryResult* results = WorldDatabase.PQuery(
        "select max(ChanceOrQuestChance) from ( "
        "select ChanceOrQuestChance from gameobject_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from spell_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from disenchant_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from fishing_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from item_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from milling_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from pickpocketing_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from prospecting_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from reference_loot_template where item = '%u' "
        "union select ChanceOrQuestChance from skinning_loot_template where item = '%u' "
        "union select 0 "
        ") a",
        i,i,i,i,i,i,i,i,i,i);

    if (results)
    {
        Field* fields = results->Fetch();
        float chance = fields[0].GetFloat();

        if (chance && chance <= 90.0)
            result = sqrt((100.0 - chance) / 10.0);

        delete results;
    }

    return result;
}


double Category::GetCategoryPriceMultiplier(uint32 untilTime, uint32 auctionHouse)
{
    double result = 1.0;

    QueryResult* results = CharacterDatabase.PQuery(
        "SELECT COUNT(*), MIN(buytime), MAX(buytime) FROM ahbot_history WHERE category = '%s' AND won = '1' AND buytime <= '%u' AND auction_house = '%u'", 
        GetName().c_str(), untilTime, auctionHouse);
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

double Category::GetItemPriceMultiplier(ItemPrototype const* proto, uint32 untilTime, uint32 auctionHouse)
{
    double result = 1.0;

    QueryResult* results = CharacterDatabase.PQuery(
        "SELECT COUNT(*), MIN(buytime), MAX(buytime) FROM ahbot_history WHERE won = '1' AND item = '%u' AND buytime <= '%u' AND auction_house = '%u'", 
        proto->ItemId, untilTime, auctionHouse);
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
    if (!price) price = proto->SellPrice * 4;
    if (!price) price = sConfig.GetIntDefault("AhBot.DefaultMinPrice", 20) * proto->ItemLevel;

    if (proto->Quality == ITEM_QUALITY_POOR)
        return price;

    return (uint32)(price * sqrt((double)proto->Quality) * sConfig.GetFloatDefault("AhBot.PriceQualityMultiplier", 1.0f));
}
