#pragma once

#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
	class ReleaseSpiritAction : public Action {
	public:
		ReleaseSpiritAction(PlayerbotAI* ai) : Action(ai, "release") {}

    public:
        virtual bool Execute(Event event)
        {
            

            if (bot->isAlive() || bot->GetCorpse())
                return false;

            bot->SetBotDeathTimer();
            bot->BuildPlayerRepop();

            WorldLocation loc;
            Corpse *corpse = bot->GetCorpse();
            corpse->GetPosition( loc );
            bot->TeleportTo( loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, bot->GetOrientation() );

            return true;
        }
    };

}