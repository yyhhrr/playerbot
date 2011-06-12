#include "../../pchdef.h"
#include "../playerbot.h"
#include "PartyMemberValue.h"

using namespace ai;

Unit* PartyMemberValue::FindPartyMember(FindPlayerPredicate &predicate)
{
    Player* bot = ai->GetAi()->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* player = gref->getSource();
        if (Check(player) && predicate.Check(player))
            return player;

        Pet* pet = player->GetPet();
        if (pet && Check(pet) && predicate.Check(pet))
            return pet;
    }
    return NULL;
}

bool PartyMemberValue::Check(Unit* player) 
{
    Player* bot = ai->GetAi()->GetBot();

    return player != bot && 
        bot->GetDistance(player) < BOT_SIGHT_DISTANCE &&
        bot->IsWithinLOS(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ());
}

bool PartyMemberValue::IsTargetOfSpellCast(Player* target, SpellEntryPredicate &predicate) 
{
    Player* bot = ai->GetAi()->GetBot();
    Group* group = bot->GetGroup();
    ObjectGuid targetGuid = target ? target->GetObjectGuid() : bot->GetObjectGuid();
    ObjectGuid corpseGuid = target && target->GetCorpse() ? target->GetCorpse()->GetObjectGuid() : ObjectGuid();

    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* player = gref->getSource();
        if (player == bot)
            continue;

        if (player->IsNonMeleeSpellCasted(true)) 
        {
            for (int type = CURRENT_GENERIC_SPELL; type < CURRENT_MAX_SPELL; type++) {
                Spell* spell = player->GetCurrentSpell((CurrentSpellTypes)type);
                if (spell && predicate.Check(spell->m_spellInfo)) { 
                    ObjectGuid unitTarget = spell->m_targets.getUnitTargetGuid();
                    if (unitTarget == targetGuid)
                        return true;

                    ObjectGuid corpseTarget = spell->m_targets.getCorpseTargetGuid();
                    if (corpseTarget == corpseGuid)
                        return true;
                }
            }
        }
    }

    return false;
}
