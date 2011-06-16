#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "CheckMountStateAction.h"

using namespace ai;

uint64 extractGuid(WorldPacket& packet);

bool CheckMountStateAction::Execute(Event event)
{
    
    Player* master = bot->GetPlayerbotAI()->GetMaster();

    WorldPacket p(event.getPacket());
    p.rpos(0);
    uint64 guid = extractGuid(p);

    if (master->IsMounted() && !bot->IsMounted())
    {
        if (!master->GetAurasByType(SPELL_AURA_MOUNTED).empty())
        {
            int32 master_speed1 = 0;
            int32 master_speed2 = 0;
            master_speed1 = master->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[1];
            master_speed2 = master->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[2];

            Mount(master_speed1, master_speed2);
            return true;
        }
    }
    else if (!master->IsMounted() && bot->IsMounted())
    {
        WorldPacket emptyPacket;
        bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
        return true;
    }
    return false;
}


void CheckMountStateAction::Mount(int32 master_speed1, int32 master_speed2)
{
    ai->RemoveAura("bear form");
    ai->RemoveAura("dire bear form");
    ai->RemoveAura("moonkin form");
    ai->RemoveAura("travel form");
    ai->RemoveAura("cat form");
    ai->RemoveAura("flight form");
    ai->RemoveAura("swift flight form");
    ai->RemoveAura("aquatic form");
    ai->RemoveAura("ghost wolf");

    
    uint32 spellMount = 0;
    for(PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
    {
        uint32 spellId = itr->first;
        if(itr->second.state == PLAYERSPELL_REMOVED || itr->second.disabled || IsPassiveSpell(spellId))
            continue;
        const SpellEntry* pSpellInfo = sSpellStore.LookupEntry(spellId);
        if (!pSpellInfo)
            continue;

        if(pSpellInfo->EffectApplyAuraName[0] != SPELL_AURA_MOUNTED)
            continue;

        if(pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
        {
            if(pSpellInfo->EffectBasePoints[1] == master_speed1 && ai->CanCastSpell(spellId, bot))
            {
                spellMount = spellId;
                break;
            }
        }
        else if((pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
            && (pSpellInfo->EffectApplyAuraName[2] == SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED))
        {
            if((pSpellInfo->EffectBasePoints[1] == master_speed1)
                && (pSpellInfo->EffectBasePoints[2] == master_speed2) && ai->CanCastSpell(spellId, bot))
            {
                spellMount = spellId;
                break;
            }
        }
        else if((pSpellInfo->EffectApplyAuraName[2] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
            && (pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED))
        {
            if((pSpellInfo->EffectBasePoints[2] == master_speed2) 
                && (pSpellInfo->EffectBasePoints[1] == master_speed1) && ai->CanCastSpell(spellId, bot))
            {
                spellMount = spellId;
                break;
            }
        }
    }

    if(spellMount > 0) 
        ai->CastSpell(spellMount, bot);
}
