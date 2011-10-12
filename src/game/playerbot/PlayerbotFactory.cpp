#include "../pchdef.h"
#include "playerbot.h"
#include "PlayerbotFactory.h"
#include "../SQLStorages.h"
#include "../ItemPrototype.h"
#include "PlayerbotAIConfig.h"
#include "../AccountMgr.h"

using namespace ai;
using namespace std;

void PlayerbotFactory::Randomize()
{
    bot->SetLevel(level);
    bot->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM);
    bot->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_CLOAK);

    //InitTalents();
    InitSkills();
    InitSpells();
    InitEquipment();
    
    //bot->SaveToDB();
}

void PlayerbotFactory::InitEquipment()
{
    for(uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        if (slot == EQUIPMENT_SLOT_TABARD || slot == EQUIPMENT_SLOT_BODY)
            continue;

        EquipItem(slot);
    }
}

bool PlayerbotFactory::EquipItem(uint8 slot)
{
    vector<uint32> items;
    for (uint32 itemId = 0; itemId < sItemStorage.MaxEntry; ++itemId)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_WEAPON && 
            proto->Class != ITEM_CLASS_ARMOR && 
            proto->Class != ITEM_CLASS_CONTAINER && 
            proto->Class != ITEM_CLASS_PROJECTILE)
            continue;

        if (proto->Class == ITEM_CLASS_ARMOR && (
            slot == EQUIPMENT_SLOT_HEAD || 
            slot == EQUIPMENT_SLOT_SHOULDERS || 
            slot == EQUIPMENT_SLOT_CHEST ||
            slot == EQUIPMENT_SLOT_WAIST || 
            slot == EQUIPMENT_SLOT_LEGS ||
            slot == EQUIPMENT_SLOT_FEET ||
            slot == EQUIPMENT_SLOT_WRISTS ||
            slot == EQUIPMENT_SLOT_HANDS))
        {
            if (bot->HasSkill(SKILL_PLATE_MAIL))
            {
                if (proto->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
                    continue;
            }
            else if (bot->HasSkill(SKILL_MAIL))
            {
                if (proto->SubClass != ITEM_SUBCLASS_ARMOR_MAIL)
                    continue;
            }
            else if (bot->HasSkill(SKILL_LEATHER))
            {
                if (proto->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER)
                    continue;
            }
        }

        if (proto->Duration & 0x80000000)
            continue;

        if (proto->Quality != sPlayerbotAIConfig.randomGearQuality)
            continue;

        uint32 requiredLevel = proto->RequiredLevel;
        if (!requiredLevel || (requiredLevel > level || requiredLevel < level - 5))
            continue;

        if (proto->Class == ITEM_CLASS_WEAPON)
        {
            switch (bot->getClass())
            {
            case CLASS_PRIEST:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                        proto->SubClass != ITEM_SUBCLASS_WEAPON_WAND &&
                        proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE)
                    continue;
                break;
            case CLASS_MAGE:
            case CLASS_WARLOCK:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                        proto->SubClass != ITEM_SUBCLASS_WEAPON_WAND &&
                        proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
                    continue;
                break;
            case CLASS_WARRIOR:
            case CLASS_PALADIN:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                        proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2)
                    continue;
                break;
            case CLASS_SHAMAN:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE)
                    continue;
                break;
            case CLASS_DRUID:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                        proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
                    continue;
                break;
            case CLASS_HUNTER:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE2)
                    continue;
                break;
            case CLASS_ROGUE:
                if (proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER)
                    continue;
                break;
            }
        }

        uint16 dest = 0;
        if (CanEquipUnseenItem(slot, dest, itemId))
            items.push_back(itemId);
    }

    if (items.empty())
        return false;

    uint32 index = urand(0, items.size() - 1);
    uint32 newItemId = items[index];
    
    Item* const oldItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
    if (oldItem)
    {
        bot->ConvertItem(oldItem, newItemId);
        return true;
    }
    else
    {
        uint16 dest;
        if (!CanEquipUnseenItem(slot, dest, newItemId))
            return false;

        Item* newItem = bot->EquipNewItem(dest, newItemId, true);
        if (newItem)
        {
            bot->AutoUnequipOffhandIfNeed();
            return true;
        }
    }
    return false;
}

bool PlayerbotFactory::CanEquipUnseenItem(uint8 slot, uint16 &dest, uint32 item)
{
    dest = 0;
    Item *pItem = Item::CreateItem(item, 1, bot);
    if (pItem)
    {
        InventoryResult result = bot->CanEquipItem(slot, dest, pItem, true );
        pItem->RemoveFromUpdateQueueOf(bot);
        delete pItem;
        return result == EQUIP_ERR_OK;
    }

    return false;
}


void PlayerbotFactory::InitSkills()
{
    uint32 maxValue = level * 5;
    SetRandomSkill(SKILL_DEFENSE);
    SetRandomSkill(SKILL_SWORDS);
    SetRandomSkill(SKILL_AXES);
    SetRandomSkill(SKILL_BOWS);
    SetRandomSkill(SKILL_GUNS);
    SetRandomSkill(SKILL_MACES);
    SetRandomSkill(SKILL_2H_SWORDS);
    SetRandomSkill(SKILL_STAVES);
    SetRandomSkill(SKILL_2H_MACES);
    SetRandomSkill(SKILL_2H_AXES);
    SetRandomSkill(SKILL_DAGGERS);
    SetRandomSkill(SKILL_THROWN);
    SetRandomSkill(SKILL_CROSSBOWS);
    SetRandomSkill(SKILL_WANDS);
    SetRandomSkill(SKILL_POLEARMS);
    SetRandomSkill(SKILL_FIST_WEAPONS);
    bot->SetSkill(SKILL_RIDING, 225, 225);

    switch (bot->getClass())
    {
    case CLASS_DEATH_KNIGHT:
    case CLASS_WARRIOR:
    case CLASS_PALADIN:
        bot->SetSkill(SKILL_PLATE_MAIL, maxValue, maxValue);
        break;
    case CLASS_SHAMAN:
    case CLASS_HUNTER:
        bot->SetSkill(SKILL_MAIL, maxValue, maxValue);
        break;
    }
}

void PlayerbotFactory::SetRandomSkill(uint16 id)
{
    uint32 maxValue = level * 5;
    uint32 curValue = urand(maxValue - level, maxValue);
    bot->SetSkill(id, curValue, maxValue);

}

void PlayerbotFactory::InitSpells()
{
    for (uint32 id = 0; id < sCreatureStorage.MaxEntry; ++id)
    {
        CreatureInfo const* co = sCreatureStorage.LookupEntry<CreatureInfo>(id);
        if (!co ||co->trainer_type != TRAINER_TYPE_CLASS || co->trainer_class != bot->getClass())
            continue;

        TrainerSpellData const* trainer_spells = sObjectMgr.GetNpcTrainerSpells(id);
        if (!trainer_spells)
            continue;

        for (TrainerSpellMap::const_iterator itr =  trainer_spells->spellList.begin(); itr !=  trainer_spells->spellList.end(); ++itr)
        {
            TrainerSpell const* tSpell = &itr->second;

            if (!tSpell)
                continue;

            if (!tSpell->learnedSpell && !bot->IsSpellFitByClassAndRace(tSpell->learnedSpell))
                continue;

            TrainerSpellState state = bot->GetTrainerSpellState(tSpell);
            if (state != TRAINER_SPELL_GREEN)
                continue;
            
            if (tSpell->IsCastable())
                bot->CastSpell(bot, tSpell->spell, true);
            else
                bot->learnSpell(tSpell->learnedSpell, false);
        }
    }
}

void PlayerbotFactory::InitTalents()
{
    bot->resetTalents(true, true);

    uint32 classMask = bot->getClassMask();
    uint32 specNo = urand(0, 2);

    for (uint32 i = 0; i < sTalentStore.GetNumRows() && bot->GetFreeTalentPoints(); ++i)
    {
        TalentEntry const *talentInfo = sTalentStore.LookupEntry(i);
        if(!talentInfo)
            continue;

        TalentTabEntry const *talentTabInfo = sTalentTabStore.LookupEntry( talentInfo->TalentTab );
        if(!talentTabInfo || talentTabInfo->tabpage != specNo)
            continue;

        if( (classMask & talentTabInfo->ClassMask) == 0 )
            continue;

        // search highest talent rank
        uint32 spellid = 0;

        for(int rank = urand(1, MAX_TALENT_RANK-1); rank >= 0; --rank)
        {
            if(talentInfo->RankID[rank]!=0)
            {
                spellid = talentInfo->RankID[rank];
                break;
            }
        }

        if(!spellid)                                        // ??? none spells in talent
            continue;

        SpellEntry const* spellInfo = sSpellStore.LookupEntry(spellid);
        if(!spellInfo || !SpellMgr::IsSpellValid(spellInfo, bot, false))
            continue;

        bot->learnSpellHighRank(spellid);
    }
}

ObjectGuid PlayerbotFactory::GetRandomBot()
{
    vector<ObjectGuid> guids;
    for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); i++)
    {
        uint32 accountId = *i;
        if (!sAccountMgr.GetCharactersCount(accountId))
            continue;
        
        QueryResult *result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account = '%u'", accountId);
        if (!result)
            continue;

        do
        {
            Field* fields = result->Fetch();
            ObjectGuid guid = ObjectGuid(fields[0].GetUInt64());
            if (!sObjectMgr.GetPlayer(guid))
                guids.push_back(guid);
        } while (result->NextRow());

        delete result;
    }

    if (guids.empty())
        return ObjectGuid();

    int index = urand(0, guids.size() - 1);
    return guids[index];
}
