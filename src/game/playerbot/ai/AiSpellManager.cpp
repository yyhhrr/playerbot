#include "../../pchdef.h"
#include "../playerbot.h"
#include "../strategy/LastMovementValue.h"
#include "../../MovementGenerator.h"

using namespace ai;
using namespace std;

typedef pair<uint32, uint8> spellEffectPair;
typedef multimap<spellEffectPair, Aura*> AuraMap;

AiSpellManager::AiSpellManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
}

bool AiSpellManager::CanCastSpell(const char* name, Unit* target)
{
    return CanCastSpell(ai->GetAiObjectContext()->GetValue<uint32>("spell id", name)->Get(), target);
}

bool AiSpellManager::CastSpell(const char* name, Unit* target) 
{
    return CastSpell(ai->GetAiObjectContext()->GetValue<uint32>("spell id", name)->Get(), target);
}

bool AiSpellManager::HasAura(const char* name, Unit* player) 
{
    return HasAura(ai->GetAiObjectContext()->GetValue<uint32>("spell id", name)->Get(), player);
}

bool AiSpellManager::HasAura(uint32 spellId, const Unit* player) 
{
	if (!spellId || !player) 
		return false;

	Unit* unit = (Unit*)player;
	if (unit->GetAura(spellId, EFFECT_INDEX_0) ||
			unit->GetAura(spellId, EFFECT_INDEX_1) ||
			unit->GetAura(spellId, EFFECT_INDEX_2))
		return true;
	return false;
}

bool AiSpellManager::HasAnyAuraOf(Unit* player, ...)
{
	if (!player)
		return false;

	va_list vl;
	va_start(vl, player);

	const char* cur = NULL;
	do {
		cur = va_arg(vl, const char*);
		if (cur && HasAura(cur, player)) {
			va_end(vl);
			return true;
		}
	}
	while (cur);

	va_end(vl);
	return false;
}

bool AiSpellManager::CanCastSpell(uint32 spellid, Unit* target)
{
	if (!spellid)
		return false;

	if (!target)
		target = bot;

	if (!bot->HasSpell(spellid) || bot->HasSpellCooldown(spellid))
		return false;

	bool positiveSpell = IsPositiveSpell(spellid);
	if (positiveSpell && bot->IsHostileTo(target))
		return false;
	
	if (!positiveSpell && bot->IsFriendlyTo(target))
		return false;

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
	if (!spellInfo)
		return false;

	ObjectGuid oldSel = bot->GetSelectionGuid();
	bot->SetSelectionGuid(target->GetObjectGuid());
	Spell *spell = new Spell(bot, spellInfo, false );
    SpellCastTargets targets;
    targets.setUnitTarget(target);
    spell->m_CastItem = ai->GetAiObjectContext()->GetValue<Item*>("item for spell", spellid)->Get();
    targets.setItemTarget(spell->m_CastItem);
	SpellCastResult result = spell->CheckCast(false);
	delete spell;
	bot->SetSelectionGuid(oldSel);

	switch (result)
	{
	case SPELL_FAILED_TOO_CLOSE:
	case SPELL_FAILED_NOT_BEHIND:
	case SPELL_FAILED_NOT_INFRONT:
	case SPELL_FAILED_NOT_STANDING:
	case SPELL_FAILED_UNIT_NOT_BEHIND:
	case SPELL_FAILED_UNIT_NOT_INFRONT:
	case SPELL_FAILED_OUT_OF_RANGE:
	case SPELL_FAILED_SUCCESS:
	case SPELL_FAILED_LINE_OF_SIGHT:
	case SPELL_FAILED_MOVING:
	case SPELL_FAILED_ONLY_STEALTHED:
	case SPELL_FAILED_ONLY_SHAPESHIFT:
	case SPELL_FAILED_SPELL_IN_PROGRESS:
	case SPELL_FAILED_TRY_AGAIN:
	case SPELL_FAILED_NOT_ON_STEALTHED:
	case SPELL_FAILED_NOT_ON_SHAPESHIFT:
	case SPELL_FAILED_NOT_IDLE:
	case SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW:
	case SPELL_FAILED_SUMMON_PENDING:
	case SPELL_FAILED_BAD_IMPLICIT_TARGETS:
	case SPELL_FAILED_BAD_TARGETS:
	case SPELL_CAST_OK:
    case SPELL_FAILED_ITEM_NOT_FOUND:
		return true;
	default:
		return false;
	}
}

bool AiSpellManager::CastSpell(uint32 spellId, Unit* target)
{
	if (!spellId)
		return false;

	if (!target)
		target = bot;

    if (!bot->isInFrontInMap(target, 10))
        bot->SetInFront(target);

    ai->GetAiObjectContext()->GetValue<uint32>("last spell id")->Set(spellId);
    lastSpellTarget = target->GetObjectGuid();
    lastCastTime = time(0);

    ai->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get().Set(NULL);

    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    bot->clearUnitState( UNIT_STAT_CHASE );
    bot->clearUnitState( UNIT_STAT_FOLLOW );

    if (!bot->IsStandState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);

    uint32 lastSpellId = ai->GetAiObjectContext()->GetValue<uint32>("last spell id")->Get();
    const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(lastSpellId);
    ObjectGuid oldSel = bot->GetSelectionGuid().GetRawValue();
    bot->SetSelectionGuid(lastSpellTarget);
    
    Spell *spell = new Spell(bot, pSpellInfo, false);
    SpellCastTargets targets;
    targets.setUnitTarget(target);
    spell->m_CastItem = ai->GetAiObjectContext()->GetValue<Item*>("item for spell", spellId)->Get();
    targets.setItemTarget(spell->m_CastItem);
    spell->prepare(&targets, false);
    
    bot->SetSelectionGuid(oldSel);

    float castTime = GetSpellCastTime(pSpellInfo);

	if (pSpellInfo->AttributesEx & SPELL_ATTR_EX_CHANNELED_1 ||
		pSpellInfo->AttributesEx & SPELL_ATTR_EX_CHANNELED_2)
		castTime += GetSpellDuration(pSpellInfo);

    castTime = ceil(castTime / 1000.0);

    uint32 globalCooldown = CalculateGlobalCooldown(spellId);
    if (castTime < globalCooldown)
        castTime = globalCooldown;

    ai->SetNextCheckDelay(castTime);
    return true;
}

void AiSpellManager::FinishSpell()
{
    uint32 lastSpellId = ai->GetAiObjectContext()->GetValue<uint32>("last spell id")->Get();
    Spell* const pSpell = bot->FindCurrentSpellBySpellId(lastSpellId);
    if (!pSpell)
        return;

    if (pSpell->IsChannelActive())
		ai->SetNextCheckDelay(GetSpellDuration(pSpell->m_spellInfo) / 1000);
}

void AiSpellManager::InterruptSpell()
{
	WorldPacket* const packet = new WorldPacket(CMSG_CANCEL_CAST, 5);
    uint32 lastSpellId = ai->GetAiObjectContext()->GetValue<uint32>("last spell id")->Get();
	*packet << lastSpellId;
	*packet << lastSpellTarget;
	bot->GetSession()->QueuePacket(packet);

    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_MAX_SPELL; type++)
        bot->InterruptSpell((CurrentSpellTypes)type);

    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_MAX_SPELL; type++)
    	bot->GetMover()->InterruptSpell((CurrentSpellTypes)type);

	SpellInterrupted(lastSpellId);
}

void AiSpellManager::SpellInterrupted(uint32 spellid)
{
    uint32 lastSpellId = ai->GetAiObjectContext()->GetValue<uint32>("last spell id")->Get();
    if (lastSpellId != spellid)
        return;

	int castTimeSpent = time(0) - lastCastTime;
	
	int32 globalCooldown = CalculateGlobalCooldown(lastSpellId);
	if (castTimeSpent < globalCooldown)
		ai->SetNextCheckDelay(globalCooldown - castTimeSpent);
	else
		ai->SetNextCheckDelay(1);

	lastSpellId = 0;
	lastSpellTarget.Set(0);
	lastCastTime = 0;
}

int32 AiSpellManager::CalculateGlobalCooldown(uint32 spellid)
{
	if (!spellid) 
		return 0;

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );

	if (!spellInfo || 
		spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_1 || 
		spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_2 || 
		spellInfo->Attributes & SPELL_ATTR_OUTDOORS_ONLY ||
		spellInfo->Attributes & SPELL_ATTR_DISABLED_WHILE_ACTIVE ||
        !spellInfo->StartRecoveryCategory)
		return 0;

    if (spellInfo->AttributesEx3 & SPELL_ATTR_EX3_REQ_WAND)
        return GLOBAL_COOLDOWN;
	
	return GLOBAL_COOLDOWN;
}

void AiSpellManager::RemoveAura(const char* name)
{
	uint32 spellid = ai->GetAiObjectContext()->GetValue<uint32>("spell id", name)->Get();
	if (spellid && HasAura(spellid, bot))
		bot->RemoveAurasDueToSpell(spellid);
}

bool AiSpellManager::IsSpellCasting(Unit* player)
{
	return player->IsNonMeleeSpellCasted(true);
}

bool AiSpellManager::HasAuraToDispel(Unit* target, uint32 dispelType) 
{
	for (uint32 type = SPELL_AURA_NONE; type < TOTAL_AURAS; ++type)
	{
		Unit::AuraList auras = target->GetAurasByType((AuraType)type);
		for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
		{
			Aura* aura = *itr;
			const SpellEntry* entry = aura->GetSpellProto();
			uint32 spellId = entry->Id;
			
			bool isPositiveSpell = IsPositiveSpell(spellId);
			if (bot->IsFriendlyTo(target) && isPositiveSpell)
				continue;

			if (bot->IsHostileTo(target) && !isPositiveSpell)
				continue;

			if (canDispel(entry, dispelType))
				return true;
		}
	}
	return false;
}

#ifndef WIN32
int strcmpi(const char *s1, const char *s2)
{
	for (; *s1 && *s2 && (toupper(*s1) == toupper(*s2)); ++s1, ++s2);
	return *s1 - *s2;
}
#endif

bool AiSpellManager::canDispel(const SpellEntry* entry, uint32 dispelType) 
{
	if (entry->Dispel == dispelType) {
		return !entry->SpellName[0] ||
			(strcmpi((const char*)entry->SpellName[0], "demon skin") &&
			strcmpi((const char*)entry->SpellName[0], "mage armor") &&
			strcmpi((const char*)entry->SpellName[0], "frost armor") &&
			strcmpi((const char*)entry->SpellName[0], "ice armor"));
	}
	return false;
}

void AiSpellManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text.size() > 5 && text.substr(0, 5) == "cast ")
	{
		Unit* unit = sObjectAccessor.GetUnit(*bot, ai->GetMaster()->GetSelectionGuid());
		bool cast = CastSpell(text.substr(text.find(" ") + 1).c_str(), unit);
		if (!cast) 
			ai->TellMaster("Cannot cast spell");
	}
}

void AiSpellManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
	case SMSG_SPELL_FAILURE:
		{
			WorldPacket p(packet);
			uint64 casterGuid = extractGuid(p);
			if (casterGuid != bot->GetGUID())
				return;
			uint8  castCount;
			uint32 spellId;
			p >> castCount;
			p >> spellId;
			SpellInterrupted(spellId);
			return;
		}

	case SMSG_SPELL_GO:
		{
			WorldPacket p(packet);
			uint64 casterGuid = extractGuid(p);
			if (casterGuid != bot->GetGUID())
				return;
			FinishSpell();
			return;
		}
    case SMSG_SPELL_DELAYED:
        {
            WorldPacket p(packet);
            uint64 casterGuid = extractGuid(p);
            if (casterGuid != bot->GetGUID())
                return;
            bot->GetPlayerbotAI()->IncreaseNextCheckDelay(1);
        }
    }
}
