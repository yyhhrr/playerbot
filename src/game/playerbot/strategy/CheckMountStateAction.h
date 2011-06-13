#pragma once

#include "Action.h"
#include "MovementActions.h"
#include "LastMovementValue.h"

namespace ai
{
    class CheckMountStateAction : public MovementAction {
    public:
        CheckMountStateAction(AiManagerRegistry* const ai) : MovementAction(ai, "check mount state") {}

        virtual bool Execute(Event event)
        {
            Player*  bot = ai->GetAi()->GetBot();
            Player* master = bot->GetPlayerbotAI()->GetMaster();
            
            WorldPacket p(event.getPacket());
            p.rpos(0);
            uint64 guid = ai->GetSpellManager()->extractGuid(p);

            if (master->IsMounted() && !bot->IsMounted())
            {
                if (!master->GetAurasByType(SPELL_AURA_MOUNTED).empty())
                {
                    int32 master_speed1 = 0;
                    int32 master_speed2 = 0;
                    master_speed1 = master->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[1];
                    master_speed2 = master->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[2];

                    ai->GetSpellManager()->Mount(master_speed1, master_speed2);
                    return true;
                }
            }
            else if (!master->IsMounted() && bot->IsMounted())
            {
                ai->GetSpellManager()->Unmount();
                return true;
            }
            return false;
        }
    };

}