#pragma once

#include "Action.h"

namespace ai
{
    class TellLosAction : public Action {
    public:
        TellLosAction(PlayerbotAI* ai) : Action(ai, "los") {}
        virtual bool Execute(Event event);

    private:
        void ListUnits(const char* title, list<Unit*> units);
        void ListGameObjects(const char* title, list<GameObject*> gos);
    };

}