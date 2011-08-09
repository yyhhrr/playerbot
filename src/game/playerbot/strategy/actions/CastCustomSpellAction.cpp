#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "CastCustomSpellAction.h"

using namespace ai;

bool CastCustomSpellAction::Execute(Event event)
{
    ObjectGuid targetGuid = master->GetSelectionGuid();
    Unit* target = targetGuid ? ai->GetUnit(targetGuid) : bot;

    string text = event.getParam();
    SpellIds spells = chat->parseSpells(text);

    if (spells.empty())
        return ai->CastSpell(text, target);

    return ai->CastSpell(*spells.begin(), target);
}
