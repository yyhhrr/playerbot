#include "PricingStrategy.h"
#include "Category.h"
#include "ItemBag.h"
#include "AhBotConfig.h"
#include "../../shared/Database/DatabaseEnv.h"

using namespace ahbot;

uint32 PricingStrategy::GetSellPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    uint32 now = time(0);
    double price = sAhBotConfig.GetItemPriceMultiplier(proto->Name1) *
        GetRarityPriceMultiplier(proto) *
        GetCategoryPriceMultiplier(now, auctionHouse) *
        GetItemPriceMultiplier(proto, now, auctionHouse) *
        sAhBotConfig.GetSellPriceMultiplier(category->GetName()) * 
        GetDefaultSellPrice(proto);
    return (uint32)price;
}

uint32 PricingStrategy::GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    uint32 untilTime = time(0) - 3600 * 36;
    double price = sAhBotConfig.GetItemPriceMultiplier(proto->Name1) *
        GetRarityPriceMultiplier(proto) *
        GetCategoryPriceMultiplier(untilTime, auctionHouse) *
        GetItemPriceMultiplier(proto, untilTime, auctionHouse) *
        sAhBotConfig.GetBuyPriceMultiplier(category->GetName()) * 
        GetDefaultBuyPrice(proto);
    return (uint32)price;
}

string PricingStrategy::ExplainSellPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    uint32 untilTime = time(0);
    ostringstream out; out << sAhBotConfig.GetItemPriceMultiplier(proto->Name1) << " * " << 
        GetRarityPriceMultiplier(proto) << " * " <<
        GetCategoryPriceMultiplier(untilTime, auctionHouse) << " * " << 
        GetItemPriceMultiplier(proto, untilTime, auctionHouse) << " * " << 
        sAhBotConfig.GetSellPriceMultiplier(category->GetName()) << " * " << 
        GetDefaultSellPrice(proto);
    return out.str();
}

string PricingStrategy::ExplainBuyPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    uint32 untilTime = time(0) - 3600 * 36;
    ostringstream out; out << sAhBotConfig.GetItemPriceMultiplier(proto->Name1) << " * " << 
        GetRarityPriceMultiplier(proto) << " * " <<
        GetCategoryPriceMultiplier(untilTime, auctionHouse) << " * " << 
        GetItemPriceMultiplier(proto, untilTime, auctionHouse) << " * " << 
        sAhBotConfig.GetBuyPriceMultiplier(category->GetName()) << " * " << 
        GetDefaultBuyPrice(proto);
    return out.str();
}

double PricingStrategy::GetRarityPriceMultiplier(ItemPrototype const* proto)
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


double PricingStrategy::GetCategoryPriceMultiplier(uint32 untilTime, uint32 auctionHouse)
{
    double result = 1.0;

    QueryResult* results = CharacterDatabase.PQuery(
        "SELECT COUNT(*), MIN(buytime), MAX(buytime) FROM ahbot_history WHERE category = '%s' AND won = '1' AND buytime <= '%u' AND auction_house = '%u'",
        category->GetName().c_str(), untilTime, auctionHouse);
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

double PricingStrategy::GetMultiplier(double count, double firstBuyTime, double lastBuyTime)
{
    double k1 = (double)count / (double)((time(0) - firstBuyTime) / 3600 / 24 + 1);
    double k2 = (double)count / (double)((time(0) - lastBuyTime) / 3600 / 24 + 1);
    return max(1.0, k1 + k2) * sAhBotConfig.priceMultiplier;
}

double PricingStrategy::GetItemPriceMultiplier(ItemPrototype const* proto, uint32 untilTime, uint32 auctionHouse)
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

uint32 PricingStrategy::ApplyQualityMultiplier(ItemPrototype const* proto, uint32 price)
{
    if (proto->Quality == ITEM_QUALITY_POOR)
        return price;

    return (uint32)(price * sqrt((double)proto->Quality) * sAhBotConfig.priceQualityMultiplier);
}

uint32 PricingStrategy::GetDefaultBuyPrice(ItemPrototype const* proto)
{
    uint32 defaultPrice = sAhBotConfig.defaultMinPrice * proto->ItemLevel * proto->ItemLevel / 10;
    uint32 buyPrice = proto->BuyPrice / 4;
    if (!buyPrice)
        buyPrice = defaultPrice;

    uint32 sellPrice = proto->SellPrice;
    if (!sellPrice)
        sellPrice = defaultPrice;

    uint32 price = (buyPrice + sellPrice + defaultPrice) / 3;
    return ApplyQualityMultiplier(proto, price);
}

uint32 PricingStrategy::GetDefaultSellPrice(ItemPrototype const* proto)
{
    return GetDefaultBuyPrice(proto);
}


uint32 BuyOnlyRarePricingStrategy::GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse)
{
    if (proto->Quality < ITEM_QUALITY_RARE)
        return 0;

    return PricingStrategy::GetBuyPrice(proto, auctionHouse);
}

