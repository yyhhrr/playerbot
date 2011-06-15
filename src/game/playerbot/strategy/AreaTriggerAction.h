#pragma once

#include "Action.h"
#include "MovementActions.h"
#include "LastMovementValue.h"

namespace ai
{
    class AreaTriggerAction : public MovementAction {
    public:
        AreaTriggerAction(PlayerbotAI* ai) : MovementAction(ai, "area trigger") {}

        virtual bool Execute(Event event)
        {
            Player*  bot = ai->GetBot();
            Player* master = bot->GetPlayerbotAI()->GetMaster();

            LastMovement& movement = ai->GetAiObjectContext()->GetValue<LastMovement&>("last movement")->Get();

            WorldPacket p(event.getPacket());
            p.rpos(0);
            p >> movement.lastAreaTrigger;
            MoveTo(master->GetMapId(), master->GetPositionX(), master->GetPositionY(), master->GetPositionZ());
            
            ai->TellMaster("Something is triggered in the area");
            return true;
        }
    };

}