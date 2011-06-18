#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TrainerAction.h"

using namespace ai;

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

void TrainerAction::List(Creature* creature, TrainerSpellAction action, SpellIds& spells) 
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

        msg << chat->formatSpell(pSpellInfo) << chat->formatMoney(cost);

        if (action && (spells.empty() || spells.find(tSpell->spell) != spells.end() || spells.find(tSpell->learnedSpell) != spells.end()))
            (this->*action)(cost, tSpell, msg);

        msg << "\r";
    }

    msg << "Total cost: " << chat->formatMoney(totalCost);

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

    SpellIds spells = chat->parseSpells(text);

    if (text == "learn")
        List(creature, &TrainerAction::Learn, spells);
    else
        List(creature, NULL, spells);

    return true;
}
