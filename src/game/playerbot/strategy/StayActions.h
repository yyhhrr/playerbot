#pragma once

#include "Action.h"
#include "MovementActions.h"

namespace ai
{
    class StayActionBase : public MovementAction {
    public:
        StayActionBase(AiManagerRegistry* const ai, const char* name) : MovementAction(ai, name) {}

    protected:
        void Stay();
        void StayLine(vector<Player*> line, float diff, float cx, float cy, float cz, float orientation, float range);  
    };

    class StayAction : public StayActionBase {
    public:
        StayAction(AiManagerRegistry* const ai) : StayActionBase(ai, "stay") {}
        virtual bool Execute(Event event);
    };

    class StayCircleAction : public StayActionBase {
    public:
        StayCircleAction(AiManagerRegistry* const ai) : StayActionBase(ai, "stay circle") {}
        virtual bool Execute(Event event);
    };

    class StayCombatAction : public StayActionBase {
    public:
        StayCombatAction(AiManagerRegistry* const ai) : StayActionBase(ai, "stay combat") {}
        virtual bool Execute(Event event);
    };

    class StayLineAction : public StayActionBase {
    public:
        StayLineAction(AiManagerRegistry* const ai) : StayActionBase(ai, "stay line") {}
        virtual bool Execute(Event event);
    };

}