#include "../../pchdef.h"
#include "../playerbot.h"
#include "SpellCastUsefulValue.h"
#include "LastSpellCastValue.h"

using namespace ai;

bool SpellCastUsefulValue::Calculate()
{
    Player* bot = ai->GetAi()->GetBot();
    Player* master = ai->GetAi()->GetMaster();

    uint32 spellid = AI_VALUE2(uint32, "spell id", qualifier.c_str());
	if (!spellid)
		return true; // there can be known alternatives

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
	if (!spellInfo)
		return true; // there can be known alternatives

    // TODO: this prevents shoot and auto-shot from changing its target
	/*if (spellInfo->AttributesEx2 & SPELL_ATTR_EX2_AUTOREPEAT_FLAG)
	{
		Spell* spell = bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL);
		if (spell && spell->m_spellInfo->Id == spellid && spell->IsAutoRepeat())
			return false;
	}*/
	
	if (spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_1 || 
		spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_2)
	{
		Spell* spell = bot->GetCurrentSpell(CURRENT_MELEE_SPELL);
		if (spell && spell->m_spellInfo->Id == spellid && spell->IsNextMeleeSwingSpell())
			return false;
	}

    uint32 lastSpellId = AI_VALUE(LastSpellCast&, "last spell id").id;
    if (spellid == lastSpellId) 
    {
        Spell* const pSpell = bot->FindCurrentSpellBySpellId(lastSpellId);
        if (pSpell)
            return false;
    }

    Item *item = AI_VALUE2(Item*, "item for spell", spellid);
    if (item && item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
        return false;

	return true;
}