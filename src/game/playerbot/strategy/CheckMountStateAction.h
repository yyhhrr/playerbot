#pragma once

#include "Action.h"
#include "MovementActions.h"
#include "LastMovementValue.h"

namespace ai
{
    class CheckMountStateAction : public MovementAction {
    public:
        CheckMountStateAction(AiManagerRegistry* const ai) : MovementAction(ai, "check mount state") {}

        virtual bool Execute(Event event);

    private:
        void Mount(int32 master_speed1, int32 master_speed2);
    };

}