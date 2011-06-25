#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "LootAction.h"

#include "../../LootObjectStack.h"

using namespace ai;

bool LootAction::Execute(Event event)
{
    if (!AI_VALUE(bool, "has available loot"))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Cannot loot: nothing more available");
        return false;
    }

    LootObject &lootObject = AI_VALUE(LootObjectStack*, "available loot")->GetLoot(BOT_SIGHT_DISTANCE);
    context->GetValue<LootObject>("loot target")->Set(lootObject);
    AI_VALUE(LootObjectStack*, "available loot")->Remove(lootObject.guid);
    return true;
}

enum ProfessionSpells
{
    ALCHEMY                      = 2259,
    BLACKSMITHING                = 2018,
    COOKING                      = 2550,
    ENCHANTING                   = 7411,
    ENGINEERING                  = 4036,
    FIRST_AID                    = 3273,
    FISHING                      = 7620,
    HERB_GATHERING               = 2366,
    INSCRIPTION                  = 45357,
    JEWELCRAFTING                = 25229,
    MINING                       = 2575,
    SKINNING                     = 8613,
    TAILORING                    = 3908
};

bool OpenLootAction::Execute(Event event)
{
    LootObject lootObject = AI_VALUE(LootObject, "loot target");
    bool result = DoLoot(lootObject);
    
    context->GetValue<LootObject>("loot target")->Set(LootObject());
    return result;
}

bool OpenLootAction::DoLoot(LootObject& lootObject)
{
    if (lootObject.IsEmpty())
        return false;

    Creature* creature = ai->GetCreature(lootObject.guid);
    if (creature && creature->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE))
    {
        WorldPacket* const packet = new WorldPacket(CMSG_LOOT, 8);
        *packet << lootObject.guid;
        bot->GetSession()->QueuePacket(packet);
        return true;
    }

    switch (lootObject.skillId)
    {
    case SKILL_MINING:
        return ai->CastSpell(MINING, bot);
    case SKILL_HERBALISM:
        return ai->CastSpell(HERB_GATHERING, bot);
    case SKILL_SKINNING:
        return ai->CastSpell(SKINNING, creature);
    case SKILL_NONE:
        return ai->CastSpell(3365, bot); //Spell 3365 = Opening?
    }

    return false;
}

bool StoreLootAction::Execute(Event event)
{
    WorldPacket p(event.getPacket()); // (8+1+4+1+1+4+4+4+4+4+1)
    ObjectGuid guid;
    uint8 loot_type;
    uint32 gold;
    uint8 items;

    p.rpos(0);
    p >> guid;      // 8 corpse guid
    p >> loot_type; // 1 loot type
    p >> gold;      // 4 money on corpse
    p >> items;     // 1 number of items on corpse

    if (gold > 0)
    {
        WorldPacket* const packet = new WorldPacket(CMSG_LOOT_MONEY, 0);
        bot->GetSession()->QueuePacket(packet);
    }
  
    for (uint8 i = 0; i < items; ++i)
    {
        uint32 itemid;
        uint32 itemcount;
        uint8 lootslot_type;
        uint8 itemindex;
        bool grab = false;

        p >> itemindex;
        p >> itemid;
        p >> itemcount;
        p.read_skip<uint32>();  // display id
        p.read_skip<uint32>();  // randomSuffix
        p.read_skip<uint32>();  // randomPropertyId
        p >> lootslot_type;     // 0 = can get, 1 = look only, 2 = master get

        if (lootslot_type != 0 && loot_type != LOOT_SKINNING)
            continue;

        if (!IsLootAllowed(itemid))
            continue;

        WorldPacket* const packet = new WorldPacket(CMSG_AUTOSTORE_LOOT_ITEM, 1);
        *packet << itemindex;
        bot->GetSession()->QueuePacket(packet);
    }

    // release loot
    WorldPacket* const packet = new WorldPacket(CMSG_LOOT_RELEASE, 8);
    *packet << guid;
    bot->GetSession()->QueuePacket(packet);
    return true;
}

bool StoreLootAction::IsLootAllowedBySkill(ItemPrototype const * proto) 
{
    switch (proto->Class)
    {
    case ITEM_CLASS_KEY:
        return true;
    case ITEM_CLASS_TRADE_GOODS:
        switch (proto->SubClass)
        {
        case ITEM_SUBCLASS_PARTS:
        case ITEM_SUBCLASS_EXPLOSIVES:
        case ITEM_SUBCLASS_DEVICES:
            return bot->HasSkill(SKILL_ENGINEERING);
        case ITEM_SUBCLASS_JEWELCRAFTING:
            return bot->HasSkill(SKILL_JEWELCRAFTING);
        case ITEM_SUBCLASS_CLOTH:
            return bot->HasSkill(SKILL_TAILORING);
        case ITEM_SUBCLASS_LEATHER:
            return bot->HasSkill(SKILL_LEATHERWORKING) || bot->HasSkill(SKILL_SKINNING);
        case ITEM_SUBCLASS_METAL_STONE:
            return (bot->HasSkill(SKILL_BLACKSMITHING) ||
                bot->HasSkill(SKILL_ENGINEERING) ||
                bot->HasSkill(SKILL_MINING));
        case ITEM_SUBCLASS_MEAT:
            return bot->HasSkill(SKILL_COOKING);
        case ITEM_SUBCLASS_HERB:
            return (bot->HasSkill(SKILL_HERBALISM) ||
                bot->HasSkill(SKILL_ALCHEMY) ||
                bot->HasSkill(SKILL_INSCRIPTION));
        case ITEM_SUBCLASS_ELEMENTAL:
            return true;
        case ITEM_SUBCLASS_ENCHANTING:
            return bot->HasSkill(SKILL_ENCHANTING);
        }
        break;
    case ITEM_CLASS_RECIPE:
        {
            if (bot->HasSpell(proto->Spells[2].SpellId))
                break;

            switch (proto->SubClass)
            {
            case ITEM_SUBCLASS_LEATHERWORKING_PATTERN:
                return bot->HasSkill(SKILL_LEATHERWORKING);
            case ITEM_SUBCLASS_TAILORING_PATTERN:
                return bot->HasSkill(SKILL_TAILORING);
            case ITEM_SUBCLASS_ENGINEERING_SCHEMATIC:
                return bot->HasSkill(SKILL_ENGINEERING);
            case ITEM_SUBCLASS_BLACKSMITHING:
                return bot->HasSkill(SKILL_BLACKSMITHING);
            case ITEM_SUBCLASS_COOKING_RECIPE:
                return bot->HasSkill(SKILL_COOKING);
            case ITEM_SUBCLASS_ALCHEMY_RECIPE:
                return bot->HasSkill(SKILL_ALCHEMY);
            case ITEM_SUBCLASS_FIRST_AID_MANUAL:
                return bot->HasSkill(SKILL_FIRST_AID);
            case ITEM_SUBCLASS_ENCHANTING_FORMULA:
                return bot->HasSkill(SKILL_ENCHANTING);
            case ITEM_SUBCLASS_FISHING_MANUAL:
                return bot->HasSkill(SKILL_FISHING);
            case ITEM_SUBCLASS_JEWELCRAFTING_RECIPE:
                return bot->HasSkill(SKILL_JEWELCRAFTING);
            }
        }
    }
    return false;
}


bool StoreLootAction::IsLootAllowed(uint32 itemid) 
{
    LootStrategy lootStrategy = AI_VALUE(LootStrategy, "loot strategy");

    if (lootStrategy == LOOTSTRATEGY_ALL)
        return true;

    set<uint32>& lootItems = AI_VALUE(set<uint32>&, "always loot list");
    if (lootItems.find(itemid) != lootItems.end())
        return true;

    ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(itemid);
    if (!proto)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: invalid item");
        return false;
    }

    uint32 max = proto->MaxCount;
    if (max > 0 && bot->HasItemCount(itemid, max, true))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: cannot have more than have");
        return false;
    }

    if (proto->StartQuest || 
        proto->Bonding == BIND_QUEST_ITEM || 
        proto->Bonding == BIND_QUEST_ITEM1 || 
        proto->Class == ITEM_CLASS_QUEST)
        return true;

    if (lootStrategy == LOOTSTRATEGY_QUEST)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: not a quest item");
        return false;
    }

    if (IsLootAllowedBySkill(proto))
        return true;

    if (lootStrategy == LOOTSTRATEGY_SKILL)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: not a quest item");
        return false;
    }

    if (proto->Quality == ITEM_QUALITY_POOR)
        return true;

    if (lootStrategy == LOOTSTRATEGY_GRAY)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: not a gray item");
        return true;
    }

    if (proto->Bonding == BIND_WHEN_PICKED_UP)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: item is BOP");
        return false;
    }

    return true;
}