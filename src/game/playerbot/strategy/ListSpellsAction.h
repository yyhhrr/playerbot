#pragma once

#include "Action.h"


namespace ai
{
    class ListSpellsAction : public Action {
    public:
        ListSpellsAction(AiManagerRegistry* const ai) : Action(ai, "spells") {}

        virtual bool Execute(Event event);
  
    };

}