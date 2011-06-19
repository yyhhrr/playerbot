#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "LootAction.h"

#include "../../LootObjectStack.h"

using namespace ai;

bool LootAction::Execute(Event event)
{
    ObjectGuid masterSelection = master->GetSelectionGuid();
    if (masterSelection) 
        AI_VALUE(LootObjectStack*, "available loot")->Add(masterSelection);

    DoLoot();

    return true;
}



void LootAction::ReleaseLoot()
{
    ObjectGuid lguid = bot->GetLootGuid();
    if( !lguid.IsEmpty()  && bot->GetSession() )
        bot->GetSession()->DoLootRelease( lguid );
}

void LootAction::DeactivateLootGameObject(LootObject &loot)
{
    GameObject* go = bot->GetPlayerbotAI()->GetGameObject(loot.guid);
    if(go)
    {
        go->SetLootState(GO_JUST_DEACTIVATED);
        go->Update(0, 0);
    }
}


void LootAction::DoLoot()
{
    if (!AI_VALUE(bool, "has available loot"))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Cannot loot: nothing more available");
        return;
    }

    LootObject &lootObject = AI_VALUE(LootObjectStack*, "available loot")->GetLoot(BOT_SIGHT_DISTANCE);
    DoLoot(lootObject);
}

void LootAction::DoLoot(LootObject &lootObject)
{
    if (!lootObject.worldObject || !lootObject.guid)
    {
        AI_VALUE(LootObjectStack*, "available loot")->Remove(lootObject.guid);
        return;
    }

    bot->GetMotionMaster()->Clear();

    float distance = bot->GetDistance(lootObject.worldObject);
    if (distance > INTERACTION_DISTANCE)
    {
        MoveNear(lootObject.worldObject, 1.0f);
        return;
    }

    bool isLooted = StoreLootItems(lootObject, LOOT_CORPSE);

    if (isLooted)
        StoreLootItems(lootObject, LOOT_SKINNING);
    else
        ai->TellMaster(LOG_LVL_DEBUG, "Not yet looted");

    AI_VALUE(LootObjectStack*, "available loot")->Remove(lootObject.guid);
}

bool LootAction::StoreLootItems(LootObject &lootObject, LootType lootType) 
{
    bot->SendLoot(lootObject.guid, lootType);

    WorldPacket p;
    bot->GetSession()->HandleLootMoneyOpcode(p);

    uint32 lootNum = lootObject.loot->GetMaxSlotInLootFor(bot);
    for( uint32 l=0; l<lootNum; l++ )
        StoreLootItem(lootObject, l, lootType);

    bool isLooted = lootObject.loot->isLooted();

    if (isLooted)
        DeactivateLootGameObject(lootObject);

    ReleaseLoot();

    return isLooted;
}

Item* LootAction::StoreItem( LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem )
{
    ItemPosCountVec dest;
    if( bot->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, item->itemid, item->count ) != EQUIP_ERR_OK )
    {
        ai->TellMaster("Insufficient bag space");
        return NULL;
    }

    Item * newitem = bot->StoreNewItem( dest, item->itemid, true, item->randomPropertyId);
    if (!newitem)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Insufficient bag space");
        return NULL;
    }

    bot->SendNewItem( newitem, uint32(item->count), false, false, true );
    bot->GetAchievementMgr().UpdateAchievementCriteria( ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM, item->itemid, item->count );

    // TODO: query item after looting
    //ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(item->itemid);
    //bot->GetPlayerbotAI()->Getai()->GetInventoryManager()->QueryItemUsage(proto);
    //bot->GetPlayerbotAI()->Getai()->GetQuestManager()->QueryQuestItem(item->itemid);

    NotifyLootItemRemoved(item, qitem, loot, lootIndex, ffaitem, conditem);

    return newitem;
}

void LootAction::NotifyLootItemRemoved(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem )
{
    if (qitem)
    {
        qitem->is_looted = true;
        if( item->freeforall || loot->GetPlayerQuestItems().size() == 1 )
            bot->SendNotifyLootItemRemoved( lootIndex );
        else
            loot->NotifyQuestItemRemoved( qitem->index );
    }
    else if (ffaitem)
    {
        ffaitem->is_looted=true;
        bot->SendNotifyLootItemRemoved( lootIndex );
    }
    else
    {
        if(conditem)
            conditem->is_looted=true;
        loot->NotifyItemRemoved( lootIndex );
    }

    if (!item->freeforall)
        item->is_looted = true;

    --loot->unlootedCount;
}

void LootAction::StoreLootItem(LootObject &lootObject, uint32 lootIndex, LootType lootType)
{
    Loot* loot = lootObject.loot;
    QuestItem *qitem=0, *ffaitem=0, *conditem=0;
    LootItem *item = loot->LootItemInSlot( lootIndex, bot, &qitem, &ffaitem, &conditem );

    if (!item || !item->AllowedForPlayer(bot))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Cannot loot: not allowed");
        return;
    }

    GameObject* go = ai->GetGameObject(lootObject.guid);
    if (go)
    {
        if (!go->isSpawned())
        {
            ai->TellMaster(LOG_LVL_DEBUG, "Cannot loot: not spawn");
            return;
        }

        if (!CheckSkill(go->GetGOInfo()->GetLockId()))
        {
            ai->TellMaster(LOG_LVL_DEBUG, "Cannot loot: insufficient skill");
            return;
        }
    }

    Creature* creature = ai->GetCreature(lootObject.guid);
    if (lootType == LOOT_SKINNING && creature && !CheckLevelBasedSkill(creature->GetCreatureInfo()->GetRequiredLootSkill(), creature->getLevel()))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Cannot loot: requires skinning");
        return;
    }

    if (!IsLootAllowed(item))
        return;

    StoreItem(item, qitem, loot, lootIndex, ffaitem, conditem);
}


bool LootAction::CheckSkill(uint32 lockId)
{
    LockEntry const *lockInfo = sLockStore.LookupEntry(lockId);
    if(!lockInfo) 
        return true;

    uint32 skillId = 0;
    uint32 reqSkillValue = 0;
    for(int i = 0; i < 8; ++i)
    {
        skillId = SkillByLockType(LockType(lockInfo->Index[i]));
        if(skillId > 0)
        {
            reqSkillValue = lockInfo->Skill[i];
            break;
        }
    }

    if (skillId == SKILL_NONE)
        return true;

    if (!bot->HasSkill(skillId) || bot->GetSkillValue(skillId) < reqSkillValue)
        return false;

    bot->UpdateGatherSkill(skillId, bot->GetSkillValue(skillId), reqSkillValue);
    return true;
}

bool LootAction::CheckLevelBasedSkill(uint32 skill, int32 level)
{
    int32 skillValue = bot->GetSkillValue(skill);
    int32 ReqValue = (skillValue < 100 ? (level-10) * 10 : level * 5);
    return ReqValue <= skillValue;
}

bool LootAction::IsLootAllowedBySkill(ItemPrototype const * proto) 
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


bool LootAction::IsLootAllowed(LootItem * item) 
{
    LootStrategy lootStrategy = AI_VALUE(LootStrategy, "loot strategy");

    if (lootStrategy == LOOTSTRATEGY_ALL)
        return true;

    set<uint32>& lootItems = AI_VALUE(set<uint32>&, "always loot list");
    if (lootItems.find(item->itemid) != lootItems.end())
        return true;

    ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(item->itemid);
    if (!proto)
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: invalid item");
        return false;
    }

    if (item->needs_quest || 
        proto->StartQuest || 
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

    if (item->freeforall || item->is_underthreshold)
        return true;

    ai->TellMaster(LOG_LVL_DEBUG, "Not allowed loot: not under threshold");
    return false;
}