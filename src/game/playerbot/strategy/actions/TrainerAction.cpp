#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TrainerAction.h"

using namespace ai;

void AppendSpellLink(const SpellEntry *sInfo, std::ostringstream& out)
{
    out << "|cffffffff|Hspell:" << sInfo->Id << "|h[" << sInfo->SpellName[LOCALE_enUS] << "]|h|r";
}


void AppendCost( uint32 cost, ostringstream& msg ) 
{
    uint32 gold = uint32(cost / 10000);
    cost -= (gold * 10000);
    uint32 silver = uint32(cost / 100);
    cost -= (silver * 100);
    msg << " ";
    if (gold > 0)
        msg << gold <<  " |TInterface\\Icons\\INV_Misc_Coin_01:8|t";
    if (silver > 0)
        msg << silver <<  " |TInterface\\Icons\\INV_Misc_Coin_03:8|t";
    msg << cost <<  " |TInterface\\Icons\\INV_Misc_Coin_05:8|t";
}


void extractSpellId(const std::string& text, uint32 &spellId)
{

    //   Link format
    //   |cffffffff|Hspell:" << spellId << ":" << "|h[" << pSpellInfo->SpellName[loc] << "]|h|r";
    //   cast |cff71d5ff|Hspell:686|h[Shadow Bolt]|h|r";
    //   012345678901234567890123456
    //        base = 16 >|  +7 >|

    uint8 pos = 0;

    int i = text.find("Hspell:", pos);
    if (i == -1)
        return;

    // DEBUG_LOG("[PlayerbotAI]: extractSpellId - first pos %u i %u",pos,i);
    pos = i + 7;     // start of window in text 16 + 7 = 23
    int endPos = text.find('|', pos);
    if (endPos == -1)
        return;

    // DEBUG_LOG("[PlayerbotAI]: extractSpellId - second endpos : %u pos : %u",endPos,pos);
    std::string idC = text.substr(pos, endPos - pos);     // 26 - 23
    spellId = atol(idC.c_str());
    pos = endPos;     // end
}


void extractSpellIdList(const std::string& text, set<uint32>& m_spellsToLearn)
{

    //   Link format
    //   |cffffffff|Hspell:" << spellId << ":" << "|h[" << pSpellInfo->SpellName[loc] << "]|h|r";
    //   cast |cff71d5ff|Hspell:686|h[Shadow Bolt]|h|r";
    //   012345678901234567890123456
    //        base = 16 >|  +7 >|

    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hspell:", pos);
        if (i == -1)
            break;

        // DEBUG_LOG("[PlayerbotAI]: extractSpellIdList - first pos %u i %u",pos,i);
        pos = i + 7;     // start of window in text 16 + 7 = 23
        int endPos = text.find('|', pos);
        if (endPos == -1)
            break;

        // DEBUG_LOG("[PlayerbotAI]: extractSpellIdList - second endpos : %u pos : %u",endPos,pos);
        std::string idC = text.substr(pos, endPos - pos);     // 26 - 23
        uint32 spellId = atol(idC.c_str());
        pos = endPos;     // end

        if (spellId)
            m_spellsToLearn.insert(spellId);
    }
}

void TrainerAction::Learn(uint32 cost, TrainerSpell const* tSpell, ostringstream& msg) 
{
    if (bot->GetMoney() < cost)
        return;

    bot->ModifyMoney(-int32(cost));
    if (tSpell->IsCastable())
        bot->CastSpell(bot, tSpell->spell, true);
    else
        bot->learnSpell(tSpell->learnedSpell, false);

    msg << " - learned";
}

void TrainerAction::List(Creature* creature, TrainerSpellAction action, set<uint32>& spells) 
{
    ostringstream msg;
    msg << "The spells I can learn and their cost:\r";

    TrainerSpellData const* cSpells = creature->GetTrainerSpells();
    TrainerSpellData const* tSpells = creature->GetTrainerTemplateSpells();
    float fDiscountMod =  bot->GetReputationPriceDiscount(creature);
    uint32 totalCost = 0;

    TrainerSpellData const* trainer_spells = cSpells;
    if (!trainer_spells)
        trainer_spells = tSpells;

    for (TrainerSpellMap::const_iterator itr =  trainer_spells->spellList.begin(); itr !=  trainer_spells->spellList.end(); ++itr)
    {
        TrainerSpell const* tSpell = &itr->second;

        if (!tSpell)
            break;

        if (!tSpell->learnedSpell && !bot->IsSpellFitByClassAndRace(tSpell->learnedSpell))
            continue;

        if  (sSpellMgr.IsPrimaryProfessionFirstRankSpell(tSpell->learnedSpell) && bot->HasSpell(tSpell->learnedSpell))
            continue;

        TrainerSpellState state = bot->GetTrainerSpellState(tSpell);
        if (state != TRAINER_SPELL_GREEN)
            continue;

        uint32 spellId = tSpell->spell;
        const SpellEntry *const pSpellInfo =  sSpellStore.LookupEntry(spellId);
        if (!pSpellInfo)
            continue;

        uint32 cost = uint32(floor(tSpell->spellCost *  fDiscountMod));
        totalCost += cost;

        AppendSpellLink(pSpellInfo, msg);
        AppendCost(cost, msg);

        if (action && (spells.empty() || spells.find(tSpell->spell) != spells.end() || spells.find(tSpell->learnedSpell) != spells.end()))
            (this->*action)(cost, tSpell, msg);

        msg << "\r";
    }

    msg << "Total cost: ";
    AppendCost(totalCost, msg);

    ai->TellMaster(msg);
}


bool TrainerAction::Execute(Event event)
{
    string text = event.getParam();
    
    Creature *creature = ai->GetCreature(master->GetSelectionGuid());
    if (!creature)
    {
        ai->TellMaster("Please select a trainer");
        return false;
    }

    if (!creature->IsTrainerOf(bot, false))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "This trainer can not teach me anything!");
        return false;
    }

    // check present spell in trainer spell list
    TrainerSpellData const* cSpells = creature->GetTrainerSpells();
    TrainerSpellData const* tSpells = creature->GetTrainerTemplateSpells();
    if (!cSpells && !tSpells)
    {
        ai->TellMaster("No spells can be learned from this trainer");
        return false;
    }

    set<uint32> spells; extractSpellIdList(text, spells);

    if (text == "learn")
        List(creature, &TrainerAction::Learn, spells);
    else
        List(creature, NULL, spells);

    return true;
}
